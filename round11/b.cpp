#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<unordered_map>
//using namespace std;
using std::min;
using std::max;
using std::swap;
using std::sort;
using std::reverse;
using std::random_shuffle;
using std::lower_bound;
using std::upper_bound;
using std::unique;
using std::vector;
using std::unordered_map;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
void open(const char *s){
#ifndef ONLINE_JUDGE
	char str[100];sprintf(str,"%s.in",s);freopen(str,"r",stdin);sprintf(str,"%s.out",s);freopen(str,"w",stdout);
#endif
}
void open2(const char *s){
#ifdef DEBUG
	char str[100];sprintf(str,"%s.in",s);freopen(str,"r",stdin);sprintf(str,"%s.out",s);freopen(str,"w",stdout);
#endif
}
int rd(){int s=0,c,b=0;while(((c=getchar())<'0'||c>'9')&&c!='-');if(c=='-'){c=getchar();b=1;}do{s=s*10+c-'0';}while((c=getchar())>='0'&&c<='9');return b?-s:s;}
void put(int x){if(!x){putchar('0');return;}static int c[20];int t=0;while(x){c[++t]=x%10;x/=10;}while(t)putchar(c[t--]+'0');}
int upmin(int &a,int b){if(b<a){a=b;return 1;}return 0;}
int upmax(int &a,int b){if(b>a){a=b;return 1;}return 0;}
const int N=500010;
int n;
char s[N];
ll ans;
namespace pam
{
	int fail[N];
	int len[N];
	int a[N];
	int next[N][30];
	int cnt;
	int f[N][20];
	int n;
	void init()
	{
		cnt=1;
		n=0;
		a[0]=-1;
		fail[0]=1;
		fail[1]=0;
		len[0]=0;
		len[1]=-1;
	}
	int append(int last,int v)
	{
		a[++n]=v;
		while(a[n-len[last]-1]!=a[n])
			last=fail[last];
		int cur=last;
		if(!next[last][v])
		{
			int now=++cnt;
			len[now]=len[cur]+2;
			last=fail[last];
			while(a[n-len[last]-1]!=a[n])
				last=fail[last];
			fail[now]=next[last][v];
			next[cur][v]=now;
		}
		return next[cur][v];
	}
	int a1[N],a2[N];
	vector<int> t[N];
	pii h[2*N];
	pii g[20][2*N];
	int ti;
	int l[2*N];
	int st[N];
	int d[N];
	void dfs(int x,int dep)
	{
		d[x]=dep;
		h[++ti]=pii(len[x],x);
		st[x]=ti;
		for(auto v:t[x])
			if(v!=fail[x])
			{
				dfs(v,dep+1);
				h[++ti]=pii(len[x],x);
			}
	}
	void gao()
	{
		init();
		a1[0]=1;
		for(int i=1;i<=::n;i++)
			a1[i]=append(a1[i-1],s[i]-'a'+1);
		a2[n+1]=1;
		for(int i=n;i>=1;i--)
		{
			a2[i]=a2[i+1];
			while(a[i+len[a2[i]]+1]!=a[i])
				a2[i]=fail[a2[i]];
			if(next[a2[i]][s[i]-'a'+1])
				a2[i]=next[a2[i]][s[i]-'a'+1];
		}
		for(int i=0;i<=cnt;i++)
			f[i][0]=fail[i];
		for(int i=0;i<=cnt;i++)
			for(int j=1;j<=19;j++)
				f[i][j]=f[f[i][j-1]][j-1];
		for(int i=2;i<=cnt;i++)
			t[fail[i]].push_back(i);
		dfs(0,0);
		for(int i=1;i<=ti;i++)
			g[0][i]=h[i];
		for(int i=1;(1<<i)<=ti;i++)
			for(int j=1;j+(1<<i)-1<=ti;j++)
				g[i][j]=min(g[i-1][j],g[i-1][j+(1<<(i-1))]);
	    l[1]=0;
	    for(int i=2;i<=ti;i++)
	    	l[i]=l[i>>1]+1;
	}
	int jump(int x,int v)
	{
		for(int i=19;i>=0;i--)
			if(len[f[x][i]]>v)
				x=f[x][i];
		if(len[x]>v)
			x=f[x][0];
		return x;
	}
	int getlca(int x,int y)
	{
//		x=st[x];
//		y=st[y];
		if(x>y)
			swap(x,y);
		int k=l[y-x+1];
		return min(g[k][x],g[k][y-(1<<k)+1]).second;
	}
}
using pam::a1;
using pam::a2;
namespace seg
{
	#define mid ((L+R)>>1)
	int lc[20000000];
	int rc[20000000];
	ll s[20000000];
	int s1[20000000];
	int s2[20000000];
	int cnt;
	void mt(int p)
	{
		s1[p]=(lc[p]?s1[lc[p]]:s1[rc[p]]);
		s2[p]=(rc[p]?s2[rc[p]]:s2[lc[p]]);
		s[p]=s[lc[p]]+s[rc[p]];
		if(s2[lc[p]]&&s1[rc[p]])
			s[p]+=pam::d[pam::getlca(s2[lc[p]],s1[rc[p]])];
	}
	int insert(int v,int L,int R)
	{
		int p=++cnt;
		if(L==R)
		{
			s1[p]=s2[p]=v;
			return p;
		}
		if(v<=mid)
			lc[p]=insert(v,L,mid);
		else
			rc[p]=insert(v,mid+1,R);
		mt(p);
		return p;
	}
	int merge(int x,int y,int L,int R,ll &v)
	{
		if(!x||!y)
			return x+y;
		if(L==R)
		{
			v-=pam::d[pam::h[L].second];
			return x;
		}
		lc[x]=merge(lc[x],lc[y],L,mid,v);
		rc[x]=merge(rc[x],rc[y],mid+1,R,v);
		mt(x);
		return x;
	}
	#undef mid
}
namespace tree
{
	vector<int> g[N];
	int rt[N];
	ll tot[N];
	void dfs(int x)
	{
		for(auto v:pam::t[x])
			if(v!=pam::fail[x])
			{
				dfs(v);
				tot[x]+=tot[v];
				rt[x]=seg::merge(rt[x],rt[v],1,pam::ti,tot[x]);
			}
		for(auto v:g[x])
		{
			rt[x]=seg::merge(rt[x],seg::insert(pam::st[v],1,pam::ti),1,pam::ti,tot[x]);
			tot[x]+=pam::d[v];
		}
		if(x)
			ans+=tot[x]-seg::s[rt[x]];
	}
	void gao()
	{
		for(int i=1;i<n;i++)
			g[a1[i]].push_back(a2[i+1]);
		dfs(0);
	}
}
namespace sa
{
	struct sa
	{
		char s[N];
		int b[N];
		int x[N];
		int y[N];
		int sa[N];
		int rk[N];
		int ht[N];
		int f[20][N];
		int l[N];
		int getmin(int x,int y)
		{
			int k=l[y-x+1];
		    return min(f[k][x],f[k][y-(1<<k)+1]);
		}
		void init()
		{
		    int i,j,k,p,sz;
		    sz=26;
		    for(i=1;i<=sz;i++)
		        b[i]=0;
		    for(i=1;i<=n;i++)
		        b[x[i]=s[i]-'a'+1]++;
		    for(i=2;i<=sz;i++)
		        b[i]+=b[i-1];
		    for(i=n;i>=1;i--)
		        sa[b[x[i]]--]=i;
		    for(k=1;k<=n;k<<=1)
		    {
		        p=0;
		        for(i=n-k+1;i<=n;i++)
		            y[++p]=i;
		        for(i=1;i<=n;i++)
		            if(sa[i]>k)
		                y[++p]=sa[i]-k;
		        for(i=1;i<=sz;i++)
		            b[i]=0;
		        for(i=1;i<=n;i++)
		            b[x[y[i]]]++;
		        for(i=2;i<=sz;i++)
		            b[i]+=b[i-1];
		        for(i=n;i>=1;i--)
		            sa[b[x[y[i]]]--]=y[i];
		        swap(x,y);
		        p=1;
		        for(i=1;i<=n;i++)
		            if(i==1||(y[sa[i]]==y[sa[i-1]]&&((sa[i]+k>n&&sa[i-1]+k>n)||(sa[i]+k<=n&&sa[i-1]+k<=n&&y[sa[i]+k]==y[sa[i-1]+k]))))
		                x[sa[i]]=p;
		            else
		                x[sa[i]]=++p;
		        if(p>=n)
		            break;
		        sz=p;
		    }
		    for(i=1;i<=n;i++)
		        rk[sa[i]]=i;
		    p=0;
		    for(i=1;i<=n;i++)
		        if(rk[i]==1)
		            ht[rk[i]]=0;
		        else
		        {
		            if(p)
		                p--;
		            while(i+p<=n&&sa[rk[i]-1]+p<=n&&s[i+p]==s[sa[rk[i]-1]+p])
		                p++;
		            ht[rk[i]]=p;
		        }
		    for(i=1;i<=n;i++)
		        f[0][i]=ht[i];
		    for(i=1;(1<<i)<=n;i++)
		        for(j=1;j<=n;j++)
		            if(j+(1<<i)-1<=n)
		                f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
		    l[1]=0;
		    for(int i=2;i<=n;i++)
		    	l[i]=l[i>>1]+1;
		}
		int query(int x,int y)
		{
			if(rk[x]>rk[y])
				swap(x,y);
			return getmin(rk[x]+1,rk[y]);
		}
	}
	lcp,lcs;
	namespace hash
	{
		const ll p[2]={1000000007,1000000009};
		ll w[2][N];
		ll h1[2][N],h2[2][N];
		ll query1(int x,int y)
		{
			ll ans=0;
			for(int i=1;i>=0;i--)
			{
				ans+=(h1[i][y]-h1[i][x-1]*w[i][y-x+1]%p[i]+p[i])%p[i];
				if(i)
					ans*=p[i];
			}
			return ans;
		}
		ll query2(int x,int y)
		{
			ll ans=0;
			for(int i=1;i>=0;i--)
			{
				ans+=(h2[i][x]-h2[i][y+1]*w[i][y-x+1]%p[i]+p[i])%p[i];
				if(i)
					ans*=p[i];
			}
			return ans;
		}
		int is_palindrome(int x,int y)
		{
			return query1(x,y)==query2(x,y);
		}
		void init()
		{
			for(int i=1;i<=n;i++)
			{
				lcp.s[i]=s[i];
				lcs.s[i]=s[n-i+1];
			}
			lcp.init();
			lcs.init();
			for(int j=0;j<=1;j++)
			{
				w[j][0]=1;
				for(int i=1;i<=n;i++)
				{
					w[j][i]=(w[j][i-1]*127)%p[j];
					h1[j][i]=(h1[j][i-1]*127+s[i])%p[j];
				}
				for(int i=n;i>=1;i--)
					h2[j][i]=(h2[j][i+1]*127+s[i])%p[j];
			}
		}
		int getlcp(int x,int y)
		{
			return lcp.query(x,y);
		}
		int getlcs(int x,int y)
		{
			return lcs.query(n-x+1,n-y+1);
		}
	}
	int pre[N];
	int ban[10000010];
	unordered_map<ull,int> map1;
	unordered_map<ull,pii> map2;
	unordered_map<ull,ll> map3;
	int check(int l,int r)
	{
		int k1=r-pam::len[pam::jump(a1[r],r-l+1)]+1;
		if(k1==l)
			return 1;
		if(hash::is_palindrome(l,k1-1))
			return 1;
		int k2=l+pam::len[pam::jump(a2[l],r-l+1)]-1;
		if(hash::is_palindrome(k2+1,r))
			return 1;
		return 0;
	}
	void gao()
	{
		hash::init();
		for(int i=1;i<=n;i++)
			pre[i]=pre[i-1]+n/i-1;
		for(int i=1;i<=n/2;i++)
		{
			int l=-1,r=-1;
			for(int j=i;j+i<=n;j+=i)
			{
				if(j<=r)
					continue;
				int l1=hash::getlcs(j,j+i);
				int l2=hash::getlcp(j,j+i);
				if(l1+l2<i+1)
					continue;
				l=j-l1+1;
				r=j+l2-1;
				if(ban[pre[i-1]+j/i])
					continue;
				for(int k=2*i;l+2*k-1<=r+i;k+=i)
					ban[pre[k-1]+(l-1)/k+1]=1;
				for(int k=l;k<=r-i+1;k++)
				{
					int _r=k+(r-k+1+i)/i*i-1;
					if(!map1[hash::query1(k,_r)])
					{
						map1[hash::query1(k,_r)]=1;
						map2[hash::query1(k,k+i-1)]=pii(k,k+i-1);
						map3[hash::query1(k,k+i-1)]+=(_r-k+1)/i;
						map3[hash::query1(k,k+i-1)]--;
						if(hash::is_palindrome(k,k+i-1))
							map3[hash::query1(k,k+i-1)]--;
					}
				}
			}
		}
		for(auto v:map2)
			if(check(v.second.first,v.second.second))
				ans-=map3[v.first];
	}
}
int main()
{
	open("b");
	scanf("%s",s+1);
	n=strlen(s+1);
	pam::gao();
	tree::gao();
	sa::gao();
	printf("%lld\n",ans);
	return 0;
}
