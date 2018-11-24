#include <bits/stdc++.h>

using namespace std;

const int md = 998244353;

inline void add(int &x, int y) {
  x += y;
  if (x >= md) {
    x -= md;
  }
}

inline void sub(int &x, int y) {
  x -= y;
  if (x < 0) {
    x += md;
  }
}

template<typename T> vector<int> suffix_array(const T &s, int n, int alpha) {
  vector<int> a(n);
  if (~alpha) {
    vector<int> bucket(alpha);
    for (int i = 0; i < n; ++i) {
      ++bucket[s[i]];
    }
    int sum = 0;
    for (int i = 0; i < alpha; ++i) {
      int add = bucket[i];
      bucket[i] = sum;
      sum += add;
    }
    for (int i = 0; i < n; ++i) {
      a[bucket[s[i]]++] = i;
    }
  } else {
    for (int i = 0; i < n; ++i) {
      a[i] = i;
    }
    sort(a.begin(), a.end(), [&](const int &x, const int &y) {
      return s[x] < s[y];
    });
  }
  vector<int> sorted_by_second(n);
  vector<int> ptr_group(n);
  vector<int> new_group(n);
  vector<int> group(n);
  group[a[0]] = 0;
  for (int i = 1; i < n; ++i) {
    group[a[i]] = group[a[i - 1]] + (s[a[i]] != s[a[i - 1]]);
  }
  int step = 1;
  while (group[a[n - 1]] < n - 1) {
    int ptr = 0;
    for (int i = n - step; i < n; ++i) {
      sorted_by_second[ptr++] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (a[i] >= step) {
        sorted_by_second[ptr++] = a[i] - step;
      }
    }
    for (int i = n - 1; ~i; --i) {
      ptr_group[group[a[i]]] = i;
    }
    for (int i = 0; i < n; ++i) {
      int x = sorted_by_second[i];
      a[ptr_group[group[x]]++] = x;
    }
    new_group[a[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (group[a[i]] != group[a[i - 1]]) {
        new_group[a[i]] = new_group[a[i - 1]] + 1;
      } else {
        int prev = a[i - 1] + step >= n ? -1 : group[a[i - 1] + step];
        int now = a[i] + step >= n ? -1 : group[a[i] + step];
        new_group[a[i]] = new_group[a[i - 1]] + (prev != now);
      }
    }
    group = new_group;
    step <<= 1;
  }
  return a;
}

template<typename T> vector<int> build_lcp(const T &s, int n, const vector<int> &sa) {
  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[sa[i]] = i;
  }
  vector<int> lcp(n - 1);
  for (int i = 0, k = 0; i < n; ++i) {
    k = max(k - 1, 0);
    if (pos[i] == n - 1) {
      k = 0;
    } else {
      int j = sa[pos[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
        ++k;
      }
      lcp[pos[i]] = k;
    }
  }
  return lcp;
}

class lcp_query_t {
 public:
  vector<vector<int>> rmq;
  vector<int> pos, zeros;
  int n;

  lcp_query_t(vector<int> sa, vector<int> lcp) {
    n = sa.size();
    zeros.resize(n);
    for (int i = 2; i < n; ++i) {
      zeros[i] = zeros[i >> 1] + 1;
    }
    pos.resize(n);
    for (int i = 0; i < n; ++i) {
      pos[sa[i]] = i;
    }
    int max_log = zeros[n - 1] + 1;
    rmq.resize(max_log);
    for (int i = 0; i < max_log; ++i) {
      rmq[i].resize(n - 1);
    }
    for (int i = 0; i < n - 1; ++i) {
      rmq[0][i] = lcp[i];
    }
    for (int i = 1; i < max_log; ++i) {
      for (int j = 0; j + (1 << i) <= n - 1; ++j) {
        rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << i - 1)]);
      }
    }
  }

  int get_lcp(int x, int y) {
    if (x == y) {
      return n - x;
    }
    x = pos[x];
    y = pos[y];
    if (x > y) {
      swap(x, y);
    }
    --y;
    int k = zeros[y - x + 1];
    return min(rmq[k][x], rmq[k][y - (1 << k) + 1]);
  }
};

int main() {
  freopen("c.in", "r", stdin);
  string s;
  cin >> s;
  int n = s.length();
  vector<int> sa = suffix_array(s, n, 256);
  vector<int> lcp = build_lcp(s, n, sa);
  lcp_query_t lcp_query(sa, lcp);
  reverse(s.begin(), s.end());
  vector<int> rev_sa = suffix_array(s, n, 256);
  vector<int> rev_lcp = build_lcp(s, n, rev_sa);
  lcp_query_t lcs_query(rev_sa, rev_lcp);
  reverse(s.begin(), s.end());
  vector<int> sum_inv(n + 1);
  for (int i = 1; i <= n; ++i) {
    sum_inv[i] = sum_inv[i - 1] + n / i - 1;
  }
  vector<bool> covered(sum_inv[n] + 1);
  vector<vector<pair<int, int>>> all(n);
  int total = 0;
  for (int i = 1; i <= n; ++i) {
    int l = -1, r = -1;
    for (int j = i - 1; j + i < n; j += i) {
      if (j > r) {
        int lcp = lcp_query.get_lcp(j, j + i);
        int lcs = lcs_query.get_lcp(n - j - 1, n - j - i - 1);
        if (lcp + lcs - 1 < i) {
          continue;
        }
        l = j - lcs + 1;
        r = j + lcp - 1;
        if (covered[sum_inv[i - 1] + (j + 1) / i]) {
          continue;
        }
        for (int x = i * 2; l + x * 2 - 1 <= r + i; x += i) {
          covered[sum_inv[x - 1] + (l + x) / x] = true;
        }
        int last = total;
        for (int k = l; k <= r - i + 1; ++k) {
          if (k < l + i) {
            ++total;
          }
          all[k + i * 2 - 1].emplace_back(i, (k - l) % i + last);
        }
      }
    }
  }
  vector<int> period(total);
  vector<int> diff(total);
  vector<int> dp(n + 1);
  dp[0] = 1;
  int sum = 1;
  for (int i = 0; i < n; ++i) {
    dp[i + 1] = sum;
    for (auto p : all[i]) {
      int l = p.first, x = p.second;
      add(period[x], dp[i + 1 - l * 2]);
      diff[x] = (dp[i + 1 - l * 2] - diff[x] + md) % md;
      sub(dp[i + 1], period[x]);
      sub(dp[i + 1], diff[x]);
    }
    add(sum, dp[i + 1]);
  }
  printf("%d\n", dp[n]);
  return 0;
}
