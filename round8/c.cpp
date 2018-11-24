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
const int N=300000;
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
	const int W=262144;
	int rev[N];
//	int w[N];
	int *w[19];
	void init()
	{
		ll s=fp(3,(p-1)/W);
		w[18]=new int[1<<17];
		w[18][0]=1;
		for(int i=1;i<1<<17;i++)
			w[18][i]=w[18][i-1]*s%p;
		for(int i=17;i>=1;i--)
		{
			w[i]=new int[1<<(i-1)];
			for(int j=0;j<1<<(i-1);j++)
				w[i][j]=w[i+1][j<<1];
		}
	}
	void ntt(int *a,int n,int t)
	{
		for(int i=1;i<n;i++)
		{
			rev[i]=(rev[i>>1]>>1)|(i&1?n>>1:0);
			if(rev[i]>i)
				swap(a[i],a[rev[i]]);
		}
		for(int i=2,l=1;i<=n;i<<=1,l++)
			for(int j=0;j<n;j+=i)
				for(int k=0;k<i/2;k++)
				{
					ll u=a[j+k];
					ll v=(ll)a[j+k+i/2]*w[l][k];
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
	void mul(int *a,int *b,int *c,int n,int m,int l=-1)
	{
		static int a1[N],a2[N];
		if(l==-1)
			l=n+m;
		int k=1;
		while(k<=n+m)
			k<<=1;
		for(int i=0;i<k;i++)
			a1[i]=a2[i]=0;
		for(int i=0;i<=n;i++)
			a1[i]=a[i];
		for(int i=0;i<=m;i++)
			a2[i]=b[i];
		ntt(a1,k,1);
		ntt(a2,k,1);
		for(int i=0;i<k;i++)
			a1[i]=(ll)a1[i]*a2[i]%p;
		ntt(a1,k,-1);
		for(int i=0;i<=l&&i<=n+m;i++)
			c[i]=a1[i];
		for(int i=n+m+1;i<=l;i++)
			c[i]=0;
	}
	void mul2(int *a,int *b,int *c,int n,int m,int l=-1)
	{
		static int a1[N],a2[N];
		if(l==-1)
			l=n+m;
		int k=1;
		while(k<=n+m)
			k<<=1;
		for(int i=0;i<k;i++)
			a1[i]=a2[i]=0;
		for(int i=0;i<=n;i++)
			a1[i]=a[i];
		for(int i=0;i<=m;i++)
			a2[i]=b[i];
		ntt(a1,k,1);
		ntt(a2,k,1);
		for(int i=0;i<k;i++)
			a1[i]=(ll)a1[i]*a2[i]%p;
		for(int i=0;i<k;i++)
			c[i]=a1[i];
	}
}
using ntt::mul;
using ntt::mul2;
int n,m1,m2;
int a1[N],a2[N];
int inv[N],fac[N],ifac[N];
int f[N],g[N];
int a[N],b[N],c[N],c1[N],c2[N];
ll binom(int x,int y)
{
	return x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0;
}
void solve(int l,int r)
{
	if(l==r)
	{
		f[l]=(ll)f[l]*fac[l-1]%p;
		g[l]=(ll)g[l]*fac[l-1]%p;
		if(a2[l-1])
			f[l]=(f[l]+1)%p;
		if(a1[0])
			f[l]=(f[l]+g[l-1])%p;
		if(l>=2)
			g[l]=(g[l]+f[l])%p;
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	if(l==1)
	{
		for(int i=2;i<=mid;i++)
			a[i]=(ll)f[i]*ifac[i-1]%p;
		for(int i=1;i<=mid;i++)
			b[i]=(ll)g[i]*ifac[i]%p;
		a[0]=a[1]=b[0]=0;
		mul(a,b,c,mid,mid);
		for(int i=mid+1;i<=r;i++)
			g[i]=(g[i]+c[i])%p;
		
		for(int i=1;i<=mid;i++)
			a[i]=(ll)g[i]*ifac[i]%p;
		for(int i=1;i<=r;i++)
			b[i]=(ll)a1[i]*ifac[i];
		a[0]=b[0]=0;
		mul(a,b,c,mid,r);
		for(int i=mid+1;i<=r;i++)
			f[i]=(f[i]+c[i-1])%p;
	}
	else
	{
		for(int i=l;i<=mid;i++)
			a[i-l]=(ll)f[i]*ifac[i-1]%p;
		for(int i=1;i<=r-l+1;i++)
			b[i]=(ll)g[i]*ifac[i]%p;
		b[0]=0;
		mul2(a,b,c1,mid-l,r-l+1);
//		for(int i=mid+1;i<=r;i++)
//			g[i]=(g[i]+c[i-l])%p;
		
		for(int i=2;i<=r-l+1;i++)
			a[i]=(ll)f[i]*ifac[i-1]%p;
		for(int i=l;i<=mid;i++)
			b[i-l]=(ll)g[i]*ifac[i]%p;
		a[0]=a[1]=0;
		mul2(a,b,c2,r-l+1,mid-l);
//		for(int i=mid+1;i<=r;i++)
//			g[i]=(g[i]+c[i-l])%p;

		int k=1;
		while(k<=r-l+1+mid-l)
			k<<=1;
		for(int i=0;i<k;i++)
			c[i]=c1[i]+c2[i];
		ntt::ntt(c,k,-1);
		for(int i=mid+1;i<=r;i++)
			g[i]=(g[i]+c[i-l])%p;
		
		for(int i=l;i<=mid;i++)
			a[i-l]=(ll)g[i]*ifac[i]%p;
		for(int i=1;i<=r-l+1;i++)
			b[i]=(ll)a1[i]*ifac[i];
		b[0]=0;
		mul(a,b,c,mid-l,r-l+1);
		for(int i=mid+1;i<=r;i++)
			f[i]=(f[i]+c[i-l-1])%p;
//		
//		for(int i=1;i<=r-l+1;i++)
//			a[i]=g[i]*ifac[i]%p;
//		for(int i=l;i<=mid;i++)
//			b[i-l]=a1[i]*ifac[i];
//		a[0]=0;
//		mul(a,b,c,r-l+1,mid-l);
//		for(int i=mid+1;i<=r;i++)
//			f[i]=(f[i]+c[i-l-1])%p;
	}
	solve(mid+1,r);
}
int main()
{
	ntt::init();
	open("c");
//	scanf("%d%d%d",&n,&m1,&m2);
	n=rd();
	m1=rd();
	m2=rd();
	int x;
	for(int i=1;i<=m1;i++)
	{
//		scanf("%d",&x);
		x=rd();
		a1[x]=1;
	}
	for(int i=1;i<=m2;i++)
	{
//		scanf("%d",&x);
		x=rd();
		a2[x]=1;
	}
	a2[0]=1;
	inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++)
	{
		inv[i]=((ll)-p/i*inv[p%i]%p+p)%p;
		fac[i]=(ll)fac[i-1]*i%p;
		ifac[i]=(ll)ifac[i-1]*inv[i]%p;
	}
	solve(1,n);
	ll ans=(f[n]+p)%p;
	printf("%lld\n",ans);
	return 0;
}
