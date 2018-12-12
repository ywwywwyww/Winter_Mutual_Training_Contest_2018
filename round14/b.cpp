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
const int N=17;
const ll p=998244353;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=a,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
pll d[N];
int e[N];
ll a[N],c[N];
int b[N][N];
int n,m;
ll C;
void fwt(ll *a,int n)
{
	for(int i=1;i<1<<n;i++)
		for(int j=0;j<1<<n;j++)
			if(i&j)
				a[j]=(a[j]+a[j^i])%p;
}
void ifwt(ll *a,int n)
{
	for(int i=1;i<1<<n;i++)
		for(int j=0;j<1<<n;j++)
			if(i&j)
				a[j]=(a[j]-a[j^i])%p;
	ll inv=fp(1<<n,p-2);
	for(int i=0;i<1<<n;i++)
		a[i]=a[i]*inv%p;
}
namespace calc
{
	pll f[N],g[N];
	pll operator *(pll a,pll b)
	{
		return pll((a.first*b.first+a.second*b.second)%p,(a.first*b.second+a.second*b.first)%p);
	}
	ll gao(int t)
	{
		ll res=0;
		ll xorsum=0;
		for(int i=1;i<=t;i++)
			xorsum^=c[i];
		for(int i=62;i>=-1;i--)
		{
			if(i==-1)
			{
				res++;
				break;
			}
			f[0]=pll(1,0);
			for(int j=1;j<=t;j++)
			{
				pll v;
				if((c[j]>>i)&1)
				{
					v.first=1ll<<i;
					v.second=(c[j]&((1ll<<i)-1))+1;
				}
				else
					v.first=(c[j]&((1ll<<i)-1))+1;
				v.first%=p;
				v.second%=p;
				f[j]=f[j-1]*v;
			}
			g[t+1]=pll(1,0);
			for(int j=t;j>=1;j--)
			{
				pll v;
				if((c[j]>>i)&1)
					v.second=(c[j]&((1ll<<i)-1))+1;
				else
					v.first=(c[j]&((1ll<<i)-1))+1;
				v.first%=p;
				v.second%=p;
				g[j]=g[j+1]*v;
			}
			for(int j=1;j<=t;j++)
				if((c[j]>>i)&1)
				{
					pll v=f[j-1]*g[j+1];
					res=(res+(((C>>i)&1)?v.second:v.first))%p;
				}
			if(((xorsum>>i)&1)!=((C>>i)&1))
				break;
		}
		return res;
	}
}
namespace init
{
	int fa[N];
	int find(int x)
	{
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	int f[1<<N],g[1<<N],h[1<<N],mi[1<<N],s[1<<N];
	void gao()
	{
		for(int i=1;i<1<<n;i++)
		{
			for(int j=1;j<=n;j++)
				if((i>>(j-1))&1)
				{
					mi[i]=j;
					break;
				}
			for(int j=1;j<=n;j++)
				if((i>>(j-1))&1)
					s[i]++;
			for(int j=1;j<=n;j++)
				fa[j]=j;
			for(int j=1;j<=n;j++)
				if((i>>(j-1))&1)
					for(int k=j+1;k<=n;k++)
						if(((i>>(k-1))&1)&&b[j][k])
							fa[find(j)]=find(k);
			int cnt=0;
			for(int j=1;j<=n;j++)
				if(((i>>(j-1))&1)&&find(j)==j)
					cnt++;
			h[i]=cnt;
		}
		g[0]=1;
		for(int i=1;i<=n;i++)
		{
			f[1<<(i-1)]=1;
			g[1<<(i-1)]=1;
		}
		for(int i=1;i<1<<n;i++)
			if(s[i]!=1)
			{
				for(int j=(i-1)&i;j;j=(j-1)&i)
					if(mi[j]==mi[i])
						g[i]=(g[i]+f[j]*g[i^j])%p;
				if(h[i]==1)
				{
					f[i]=-g[i];
					g[i]=0;
				}
			}
	}
}
ll f[N][1<<N];
ll ans;
void add(ll &a,ll b)
{
	a=(a+b)%p;
}
void dp()
{
	f[1][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<1<<n;j++)
			if((j>>(i-1))&1)
				add(f[i+1][j^(1<<(i-1))],f[i][j]);
			else
			{
				int orzzjt=((1<<n)-1)^(j|((1<<(i-1))-1));
				for(int k=orzzjt;k;k=(k-1)&orzzjt)
					if(init::mi[k]==i&&init::h[k]==1)
						add(f[i+1][(j|k)^(init::s[k]&1?0:1<<(i-1))],f[i][j]*init::f[k]%p*(init::s[k]&1?1:a[i]%p+1));
			}
	for(int i=0;i<1<<n;i++)
	{
		int t=0;
		for(int j=1;j<=n;j++)
			if((i>>(j-1))&1)
				c[++t]=a[j];
		ll temp=calc::gao(t);
		ans=(ans+f[n+1][i]*temp)%p;
	}
}
int main()
{
	open("b");
	scanf("%d%d%lld",&n,&m,&C);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		d[i].first=a[i];
		d[i].second=i;
	}
	sort(d+1,d+n+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=d[i].first;
		e[d[i].second]=i;
	}
	int x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		x=e[x];
		y=e[y];
		b[x][y]=b[y][x]=1;
	}
//	for(int i=1;i<=n;i++)
//		c[i]=a[i];
//	ll ans=calc::calc(n);
//	ans=(ans%p+p)%p;
//	printf("%lld\n",ans);
	init::gao();
	dp();
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
