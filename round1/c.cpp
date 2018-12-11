#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
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
const int N=100010;
vector<int> g[N];
ll f[N];
ll h[N];
int s[N];
int n;
vector<int> c;
vector<int> e;
void dfs1(int x)
{
	s[x]=1;
	f[x]=0;
	for(auto v:g[x])
	{
		dfs1(v);
		s[x]+=s[v];
		f[x]+=f[v];
	}
	c.clear();
	for(auto v:g[x])
		c.push_back(s[v]);
	int sum=1;
	sort(c.begin(),c.end());
	for(auto v:c)
	{
		f[x]+=sum;
		sum+=v;
	}
}
void dfs2(int x)
{
	c.clear();
	ll tot=0;
	for(auto v:g[x])
	{
		tot+=f[v];
		c.push_back(s[v]);
	}
	if(x!=1)
	{
		tot+=h[x];
		c.push_back(n-s[x]);
	}
	e.clear();
	sort(c.begin(),c.end());
	int sum=1;
	for(auto v:c)
	{
		e.push_back(sum);
		tot+=sum;
		sum+=v;
	}
	for(auto v:g[x])
	{
		ll temp=tot-f[v];
		int y=lower_bound(c.begin(),c.end(),s[v])-c.begin();
		temp-=e[y];
		temp-=((int)c.size()-y-1)*s[v];
		h[v]=temp;
	}
	for(auto v:g[x])
		dfs2(v);
}
void solve()
{
	dfs1(1);
	dfs2(1);
	ll ans=0x7fffffff;
	for(int i=1;i<=n;i++)
	{
		ll tot=0;
		c.clear();
		for(auto v:g[i])
		{
			c.push_back(s[v]);
			tot+=f[v];
		}
		if(i!=1)
		{
			c.push_back(n-s[i]);
			tot+=h[i];
		}
		sort(c.begin(),c.end());
		ll sum1=1,sum2=1;
		int t=0;
		for(auto v:c)
		{
			t++;
			if(t&1)
			{
				tot+=sum1;
				sum1+=v;
			}
			else
			{
				tot+=sum2;
				sum2+=v;
			}
		}
		ans=min(ans,tot);
	}
	printf("%lld\n",ans);
}
int main()
{
	open("c");
	scanf("%d",&n);
	int x,y;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
	}
	solve();
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&x);
		y=++n;
		g[x].push_back(y);
		solve();
	}
	return 0;
}
