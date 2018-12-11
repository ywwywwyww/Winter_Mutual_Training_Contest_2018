#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<queue>
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
using std::priority_queue;
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
const ll p=998244353;
const int N=600000;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
ll fac[2*N],ifac[2*N],inv[2*N];
ll binom(int x,int y)
{
	if(x==y)
		return 1;
	return x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0;
}
namespace ntt
{
	const int W=524288;
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
		ntt(a1,k,1);
		ntt(a2,k,1);
		for(int i=0;i<k;i++)
			a1[i]=a1[i]*a2[i]%p;
		ntt(a1,k,-1);
		for(int i=0;i<=l;i++)
			c[i]=a1[i];
	}
}
int a[N];
int s[N];
int n;
ll f[N];
ll g[N];
ll *c[N];
ll h[N];
ll b[N];
priority_queue<pii,vector<pii>,std::greater<pii> > q;
int main()
{
	open("c");
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		a[i]=rd();
		s[i]=s[i-1]+a[i];
	}
	if(n==1)
	{
		printf("%d\n",s[1]);
		return 0;
	}
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
	for(int i=2;i<=400000;i++)
	{
		inv[i]=-p/i*inv[p%i]%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
	ntt::init();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=a[i];j++)
			f[j]=binom(a[i]+j-1,a[i]-j)*fac[j-1]%p;
		if(i==1)
			for(int j=1;j<=a[i];j++)
				f[j]=f[j]*inv[j]%p;
		for(int j=0;j<=a[i];j++)
			g[j]=(j&1?-1:1)*ifac[j]%p;
		reverse(f,f+a[i]+1);
		ntt::mul(f,g,h,a[i]-1,a[i],a[i]);
		reverse(h,h+a[i]+1);
		h[0]=0;
		for(int j=1;j<=a[i];j++)
			h[j]=h[j]*ifac[j-1]%p;
		if(i==1)
		{
			for(int j=0;j<=a[i];j++)
				b[j]=0;
			for(int j=1;j<=a[i];j++)
				b[j-1]=h[j];
			for(int j=2;j<=a[i];j++)
				b[j-2]=(b[j-2]-h[j])%p;
			for(int j=0;j<=a[i];j++)
				h[j]=b[j];
		}
		for(int j=0;j<=a[i];j++)
			h[j]=h[j]*ifac[j]%p;
		c[i]=new ll[a[i]+1];
		for(int j=0;j<=a[i];j++)
			c[i][j]=h[j];
		q.push(pii(a[i],i));
	}
	int cnt=n;
	for(int i=1;i<n;i++)
	{
		pii v1=q.top();
		q.pop();
		pii v2=q.top();
		q.pop();
		cnt++;
		c[cnt]=new ll[v1.first+v2.first+1];
		ntt::mul(c[v1.second],c[v2.second],c[cnt],v1.first,v2.first,v1.first+v2.first);
		q.push(pii(v1.first+v2.first,cnt));
	}
	ll ans=0;
	for(int i=1;i<=s[n];i++)
		ans=(ans+c[cnt][i]*fac[i])%p;
	ans=ans*s[n]%p;
	ans=(ans+p)%p;
	printf("%lld\n",ans);
	return 0;
}
