#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<bitset>
using namespace std;
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
const ll p=1000000007;
const int N=1010;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
typedef bitset<N> orzzjt;
typedef pair<orzzjt,orzzjt> zjtakioi2019;
ll pw[N*N];
ll f[N][N],g[N][N];
void add(ll &a,ll b)
{
	a=(a+b)%p;
}
int n,m,k;
ll solve(int x)
{
	ll res=0;
	for(int i=x;i<=n&&i<=m;i++)
		res=(res+f[m][i]*g[i][x]%p*pw[k*(m-i)])%p;
	res=res*fp(f[k][x],p-2)%p;
	res=(res%p+p)%p;
	return res;
}
ll e[N];
void init()
{
	pw[0]=1;
	for(int i=1;i<=1000000;i++)
		pw[i]=pw[i-1]*2%p;
	f[0][0]=1;
	for(int i=0;i<1000;i++)
		for(int j=0;j<=i&&j<=n;j++)
			if(f[i][j])
			{
				add(f[i+1][j],f[i][j]*pw[j]);
				add(f[i+1][j+1],f[i][j]*(pw[n]-pw[j]));
			}
	g[0][0]=1;
	for(int i=0;i<1000;i++)
		for(int j=0;j<=i&&j<=k;j++)
			if(g[i][j])
			{
				add(g[i+1][j],g[i][j]*pw[j]);
				add(g[i+1][j+1],g[i][j]*(pw[k]-pw[j]));
			}
	for(int i=0;i<=n&&i<=k;i++)
		e[i]=solve(i);
}
zjtakioi2019 a[N];
orzzjt b[N];
int t;
int r;
void insert(orzzjt x,int v)
{
	orzzjt y;
	y.set(v);
	for(int i=1000;i>=1;i--)
		if(x[i])
		{
			if(!a[i].first.any())
			{
				a[i].first=x;
				a[i].second=y;
				r++;
				return;
			}
			x^=a[i].first;
			y^=a[i].second;
		}
	t++;
	b[t]=y;
}
void erase(int x)
{
	for(int i=1;i<=t;i++)
		if(b[i][x])
		{
			swap(b[i],b[t]);
			t--;
			for(int j=1;j<=1000;j++)
				if(a[j].second[x])
					a[j].second^=b[t+1];
			for(int j=1;j<=t;j++)
				if(b[j][x])
					b[j]^=b[t+1];
			return;
		}
	for(int i=1;i<=1000;i++)
		if(a[i].second[x])
		{
			for(int j=i+1;j<=1000;j++)
				if(a[j].second[x])
				{
					a[j].first^=a[i].first;
					a[j].second^=a[i].second;
				}
			a[i].first=a[i].second=orzzjt();
			r--;
			return;
		}
}
int main()
{
	open("c");
	int q,type;
	scanf("%d%d%d%d%d",&n,&m,&k,&q,&type);
	init();
	int x,y;
	for(int i=1;i<=n;i++)
	{
		orzzjt s;
		for(int j=1;j<=k;j++)
		{
			scanf("%d",&x);
			if(x)
				s.set(j);
		}
		insert(s,i);
	}
	ll ans=e[r];
	printf("%lld\n",ans);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&x);
		x^=type*ans;
		erase(x);
		orzzjt s;
		for(int j=1;j<=k;j++)
		{
			scanf("%d",&y);
			if(y)
				s.set(j);
		}
		insert(s,x);
		ans=e[r];
		printf("%lld\n",ans);
	}
	return 0;
}
