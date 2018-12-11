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
const ll p=998244353;
const int N=300000;
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
	ll w[N];
	void init()
	{
		ll s=fp(3,(p-1)/W);
		w[0]=1;
		for(int i=1;i<W;i++)
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
	void getinv(ll *a,ll *b,int n)
	{
		if(n==1)
		{
			b[0]=fp(a[0],p-2);
			return;
		}
		getinv(a,b,n>>1);
		static ll a1[N],a2[N];
		for(int i=0;i<n;i++)
			a1[i]=a[i];
		for(int i=n;i<2*n;i++)
			a1[i]=0;
		for(int i=0;i<n>>1;i++)
			a2[i]=b[i];
		for(int i=n>>1;i<n<<1;i++)
			a2[i]=0;
		ntt(a1,n<<1,1);
		ntt(a2,n<<1,1);
		for(int i=0;i<n<<1;i++)
			a1[i]=a2[i]*(2-a1[i]*a2[i]%p)%p;
		ntt(a1,n<<1,-1);
		for(int i=0;i<n;i++)
			b[i]=a1[i];
	}
}
namespace gao
{
	struct mat
	{
		ll a[2][2];
		mat()
		{
			memset(a,0,sizeof a);
		}
		ll *operator [](int x)
		{
			return a[x];
		}
	};
	mat operator *(mat a,mat b)
	{
		mat c;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
				for(int k=0;k<=1;k++)
					c[i][j]=(c[i][j]+a[i][k]*b[k][j])%p;
		return c;
	}
	mat fp(mat a,ll b)
	{
		mat s;
		s[0][0]=s[1][1]=1;
		for(;b;b>>=1,a=a*a)
			if(b&1)
				s=s*a;
		return s;
	}
	pll gao(ll x,int n)
	{
		mat a;
		a[0][0]=0;
		a[0][1]=-x;
		a[1][0]=1;
		a[1][1]=1;
		a=fp(a,n-1);
		mat c;
		c[0][0]=1;
		c[0][1]=1;
		c=c*a;
		return pll(c[0][0],c[0][1]);
	}
}
int n,m;
ll a[N],b[N],c[N];
int main()
{
	open("a");
	scanf("%d%d",&n,&m);
	if(n<m)
	{
		printf("0\n");
		return 0;
	}
	m++;
	ntt::init();
	int k=1;
	while(k<m)
		k<<=1;
	a[0]=1;
	a[1]=0;
	b[0]=1;
	b[1]=-1;
	ntt::ntt(a,k,1);
	ntt::ntt(b,k,1);
	for(int i=0;i<k;i++)
	{
		pll v=gao::gao(ntt::w[ntt::W/k*i],m);
		a[i]=v.first;
		b[i]=v.second;
	}
	ntt::ntt(a,k,-1);
	ntt::ntt(b,k,-1);
	int k2=k;
	while(k2<=n)
		k2<<=1;
	for(int i=k;i<k2;i++)
		b[i]=0;
	ntt::getinv(b,c,k2);
	ll ans=0;
	for(int i=0;i<=n;i++)
		if(i<k&&n-i<k2)
			ans=(ans+a[i]*c[n-i])%p;
	ans=(ans+p)%p;
	printf("%lld\n",ans);
	return 0;
}
