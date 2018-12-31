#pragma GCC optimize(2)
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
typedef long double ldb;
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
const int N=100000;
const ll p=998244353;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
namespace ntt
{
	const int W=65536;
	ll w[N];
	int rev[N];
	void init()
	{
		ll s=fp(3,(p-1)/W);
		w[0]=1;
		for(int i=1;i<W/2;i++)
			w[i]=w[i-1]*s%p;
	}
	void ntt(ll *a,int n,int t)
	{
		for(int i=1;i<n;i++)
		{
			rev[i]=(rev[i>>1]>>1)|(i&1?n>>1:0);
			if(rev[i]>i)
				swap(a[i],a[rev[i]]);
		}
		for(int i=2;i<=n;i<<=1)
			for(int j=0;j<n;j+=i)
				for(int k=0;k<i/2;k++)
				{
					ll u=a[j+k];
					ll v=a[j+k+i/2]*w[W/i*k];
					a[j+k]=(u+v)%p;
					a[j+k+i/2]=(u-v)%p;
				}
		if(t==-1)
		{
			reverse(a+1,a+n);
			ll inv=fp(n,p-2);
			for(int i=0;i<n;i++)
				a[i]=a[i]*inv%p;
		}
	}
	void mul(ll *a,ll *b,ll *c,int n,int m,int l)
	{
		static ll a1[N],a2[N];
		int k=1;
		while(k<=n+m)
			k<<=1;
		for(int i=0;i<k;i++)
			a1[i]=a2[i]=0;
		for(int i=0;i<=n;i++)
			a1[i]=a[i];
		for(int i=0;i<=m;i++)
			a2[i]=b[i];
		ntt::ntt(a1,k,1);
		ntt::ntt(a2,k,1);
		for(int i=0;i<k;i++)
			a1[i]=a1[i]*a2[i]%p;
		ntt::ntt(a1,k,-1);
		for(int i=0;i<=l;i++)
			c[i]=a1[i];
	}
}
ll f[60][60000];
ll g[60][60000];
int n,k;
ll inv[N],fac[N],ifac[N];
ll c[N];
ll s[N];
void init()
{
	inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=60000;i++)
	{
		inv[i]=-p/i*inv[p%i]%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
}
ll binom(int x,int y)
{
	return fac[x]*ifac[y]%p*ifac[x-y]%p;
}
int main()
{
	open("a");
	init();
	ntt::init();
	scanf("%d%d",&n,&k);
	f[0][0]=1;
	for(int i=0;i<k;i++)
		c[i]=ifac[i];
	for(int i=1;i<=n;i++)
		ntt::mul(f[i-1],c,f[i],(i-1)*(k-1),k-1,i*(k-1));
	for(int i=1;i<=n;i++)
		for(int j=k-1;j<=i*(k-1);j++)
			g[i][j]=f[i-1][j-k+1]*ifac[k-1]%p*i%p;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n*k;j++)
			s[i]=(s[i]+g[i][j-1]*fac[j-1]%p*fp(inv[i],j)%p*j%p*n%p*inv[i])%p;
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+s[i]*binom(n,i)%p*((i+1)&1?-1:1))%p;
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
