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
const int N=530010;
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
	const int W=524288;
	ll w[N];
	int rev[N];
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
		l=min(l,n+m);
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
			a1[i]=a1[i]*a2[i]%p;
		ntt(a1,k,-1);
		for(int i=0;i<=l;i++)
			c[i]=a1[i];
	}
}
ll fac[N],ifac[N],inv[N];
void init()
{
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
	for(int i=2;i<=500000;i++)
	{
		inv[i]=-p/i*inv[p%i]%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
}
ll binom(ll x,ll y)
{
	return x==y?1:(x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0);
}
ll calc(int x,int y)
{
	return binom(x+y,x);
}
ll *f1,*f2,*g1,*g2;
int H,W;
int n;
int h[N],w[N],x1[N],y1[N],x2[N],y2[N];
int main()
{
	open("c");
	scanf("%d%d",&H,&W);
	init();
	scanf("%d",&n);
	for(int i=0;i<=n+1;i++)
	{
		scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
		h[i]=x2[i]-x1[i]+1;
		w[i]=y2[i]-y1[i]+1;
	}
	f1=new ll[w[0]];
	f2=new ll[h[0]];
	for(int i=0;i<w[0];i++)
		f1[i]=calc(i+1,h[0]);
	for(int i=0;i<h[0];i++)
		f2[i]=calc(i+1,w[0]);
	
	for(int i=1;i<=n+1;i++)
	{
		g1=new ll[h[i]];
		g2=new ll[w[i]];
		for(int j=0;j<h[i];j++)
			g1[j]=0;
		for(int j=0;j<w[i];j++)
			g2[j]=0;
		
		for(int j=0;j<w[i-1];j++)
			for(int k=0;k<h[i];k++)
				g1[k]=(g1[k]+f1[j]*calc(x1[i]-x2[i-1]+k-1,y1[i]-y1[i-1]-j-1))%p;
		
		for(int j=0;j<h[i-1];j++)
			for(int k=0;k<w[i];k++)
				g2[k]=(g2[k]+f2[j]*calc(y1[i]-y2[i-1]+k-1,x1[i]-x1[i-1]-j-1))%p;
				
		if(x2[i-1]+2<=x1[i])
			for(int j=0;j<h[i-1];j++)
				for(int k=0;k<h[i];k++)
					g1[k]=(g1[k]+f2[j]*calc(x1[i]-x2[i-1]-2,y1[i]-y1[i-1]+k-j))%p;
		
		if(y2[i-1]+2<=y1[i])
			for(int j=0;j<w[i-1];j++)
				for(int k=0;k<w[i];k++)
					g2[k]=(g2[k]+f1[j]*calc(y1[i]-y2[i-1]-2,x1[i]-x1[i-1]+k-j))%p;
		
		if(i<=n)
		{
			f1=new ll[w[i]];
			f2=new ll[h[i]];
			for(int i=0;i<w[i];i++)
				f1[i]=0;
			for(int i=0;i<h[i];i++)
				f2[i]=0;
			
			for(int j=0;j<h[i];j++)
				for(int k=0;k<w[i];k++)
					f1[k]=(f1[k]+g1[j]*calc(h[i]-j-1,k))%p;
			
			for(int j=0;j<w[i];j++)
				for(int k=0;k<h[i];k++)
					f2[k]=(f2[k]+g2[j]*calc(w[i]-j-1,k))%p;
			
			for(int j=0;j<h[i];j++)
				for(int k=j;k<h[i];k++)
					f1[k]=(f1[k]+g1[j]*calc(k-j,w[i]-1))%p;
			
			for(int j=0;j<w[i];j++)
				for(int k=j;k<w[i];k++)
					f2[k]=(f2[k]+g2[j]*calc(k-j,h[i]-1))%p;
		}
	}
	
	ll ans=0;
	
	for(int i=0;i<h[n+1];i++)
		ans=(ans+g1[i]*calc(h[n+1]-i,w[n+1]))%p;
	for(int i=0;i<w[n+1];i++)
		ans=(ans+g2[i]*calc(w[n+1]-i,h[n+1]))%p;
	
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	
	return 0;
}
