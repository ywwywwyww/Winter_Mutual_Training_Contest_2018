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
const ll p1=998244353;
const int N=530000;
const db pi=acos(-1);
ll fp(ll a,ll b,ll p)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
ll n,p,g;
ll n1,n2;
ll e1[N],e2[N];
namespace fft
{
	struct cp
	{
		db x,y;
		cp(db a=0,db b=0):x(a),y(b){}
	};
	cp operator +(cp a,cp b){return cp(a.x+b.x,a.y+b.y);}
	cp operator -(cp a,cp b){return cp(a.x-b.x,a.y-b.y);}
	cp operator *(cp a,cp b){return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
	cp operator /(cp a,int b){return cp(a.x/b,a.y/b);}
	cp muli(cp a){return cp(-a.y,a.x);}
	cp divi(cp a){return cp(a.y,-a.x);}
	cp conj(cp a){return cp(a.x,-a.y);}
	const int W=524288;
	cp w[N];
	int rev[N];
	void init()
	{
		for(int i=0;i<W/2;i++)
			w[i]=cp(cos(2*pi/W*i),sin(2*pi/W*i));
	}
	void fft(cp *a,int n,int t)
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
					cp u=a[j+k];
					cp v=a[j+k+i/2]*w[W/i*k];
					a[j+k]=u+v;
					a[j+k+i/2]=u-v;
				}
		if(t==-1)
		{
			reverse(a+1,a+n);
			for(int i=0;i<n;i++)
				a[i]=a[i]/n;
		}
	}
	void fft(db *a,db *b,cp *c,cp *d,int n)
	{
		static cp a1[N],a2[N];
		for(int i=0;i<n;i++)
			a1[i]=cp(a[i],b[i]);
		fft(a1,n,1);
		for(int i=0;i<n;i++)
			a2[i]=conj(a1[i]);
		reverse(a2+1,a2+n);
		for(int i=0;i<n;i++)
		{
			c[i]=(a1[i]+a2[i])/2;
			d[i]=divi(a1[i]-a2[i])/2;
		}
	}
	void ifft(db *a,db *b,cp *c,cp *d,int n)
	{
		static cp a1[N];
		for(int i=0;i<n;i++)
			a1[i]=c[i]+muli(d[i]);
		fft(a1,n,-1);
		for(int i=0;i<n;i++)
		{
			a[i]=a1[i].x;
			b[i]=a1[i].y;
		}
	}
	void mul(ll *a,ll *b,ll *c,int n,int m,int l,ll p)
	{
		const static int M=1<<16;
		static db a1[N],a2[N],b1[N],b2[N],c1[N],c2[N],d1[N],d2[N];
		static cp a3[N],a4[N],b3[N],b4[N],c3[N],c4[N],d3[N],d4[N];
		int k=1;
		while(k<=n+m)
			k<<=1;
		for(int i=0;i<k;i++)
			a1[i]=a2[i]=b1[i]=b2[i]=0;
		for(int i=0;i<=n;i++)
		{
			a[i]=(a[i]+p)%p;
			a1[i]=a[i]/M;
			a2[i]=a[i]%M;
		}
		for(int i=0;i<=m;i++)
		{
			b[i]=(b[i]+p)%p;
			b1[i]=b[i]/M;
			b2[i]=b[i]%M;
		}
		fft(a1,a2,a3,a4,k);
		fft(b1,b2,b3,b4,k);
		for(int i=0;i<k;i++)
		{
			c3[i]=a3[i]*b3[i];
			c4[i]=a3[i]*b4[i];
			d3[i]=a4[i]*b3[i];
			d4[i]=a4[i]*b4[i];
		}
		ifft(c1,c2,c3,c4,k);
		ifft(d1,d2,d3,d4,k);
		for(int i=0;i<=l;i++)
			c[i]=((ll)(c1[i]+0.5)%p*M%p*M%p+(ll)(c2[i]+0.5)%p*M%p+(ll)(d1[i]+0.5)%p*M%p+(ll)(d2[i]+0.5)%p)%p;
	}
	void mul2(ll *a,ll *b,ll *c,int n,ll p)
	{
		static ll a1[N],a2[N],a3[N];
		for(int i=1;i<n;i++)
		{
			a1[e2[i]]=a[i];
			a2[e2[i]]=b[i];
		}
		mul(a1,a2,a3,n-2,n-2,2*n-4,p);
		for(int i=1;i<n;i++)
			c[i]=0;
		for(int i=0;i<=2*n-4;i++)
			c[e1[i%(n-1)]]=(c[e1[i%(n-1)]]+a3[i])%p;
	}
}
ll inv[N],fac[N],ifac[N];
void init()
{
	inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<p;i++)
	{
		inv[i]=(-p/i*inv[p%i]%p+p)%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
}
ll binom(int x,int y)
{
	return x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0;
}
int check()
{
	ll s=1;
	for(int i=1;i<=p;i++)
	{
		s=s*g%p;
		if(s==1)
		{
			if(i==p-1)
				return 1;
			return 0;
		}
	}
	return 0;
}
void getg()
{
	for(g=1;;g++)
		if(check())
			break;
	e1[0]=1;
	for(int i=1;i<p-1;i++)
		e1[i]=e1[i-1]*g%p;
	for(int i=0;i<p-1;i++)
		e2[e1[i]]=i;
}
namespace gao1
{
	ll ans[N];
	ll s[N];
	void solve(int n)
	{
		if(!n)
		{
			s[0]=1;
			return;
		}
		if(n&1)
		{
			solve(n-1);
			for(int i=n-1;i>=0;i--)
			{
				s[i+1]=(s[i+1]+s[i])%p;
				s[i]=s[i]*n%p;
			}
		}
		else
		{
			solve(n>>1);
			static ll a1[N],a2[N],a3[N];
			for(int i=0;i<=n>>1;i++)
			{
				a1[i]=fp((n>>1),i,p)*ifac[i]%p;
				a2[i]=s[i]*fac[i]%p;
			}
			reverse(a2,a2+(n>>1)+1);
			fft::mul(a1,a2,a3,n>>1,n>>1,n>>1,p);
			reverse(a3,a3+(n>>1)+1);
			for(int i=0;i<=n>>1;i++)
				a3[i]=a3[i]*ifac[i]%p;
			fft::mul(s,a3,s,n>>1,n>>1,n,p);
		}
	}
	void gao()
	{
		solve(n2);
		for(int i=0;i<=n2;i++)
			if(s[i])
				ans[s[i]]++;
	}
}
namespace gao2
{
	ll ans[N];
	int a[N],t;
	ll s[N];
	int v[N];
	void gao()
	{
		static ll a1[N],a2[N];
		for(ll _=n1;_;)
		{
			a[++t]=_%p;
			_/=p;
		}
		ans[1]=1;
		for(int j=1;j<=t;j++)
		{
			v[j]=(p==2&&j>1?1:-1);
			for(int i=0;i<p;i++)
				a1[i]=0;
			for(int i=0;i<=a[j];i++)
				a1[(binom(a[j],i)*(i&1?v[j]:1)%p+p)%p]++;
			fft::mul2(ans,a1,a2,p,p1);
			for(int i=1;i<p;i++)
				ans[i]=a2[i];
		}
	}
}
ll ans[N];
int main()
{
	open("b");
	fft::init();
	scanf("%lld%lld",&n,&p);
	init();
	getg();
	n1=n/p,n2=n%p;
	if(n2==p-1)
	{
		n1++;
		n2=0;
	}
	gao1::gao();
	gao2::gao();
	fft::mul2(gao1::ans,gao2::ans,ans,p,p1);
	ans[0]=(n+1)%p1;
	for(int i=1;i<p;i++)
		ans[0]=(ans[0]-ans[i])%p1;
	for(int i=0;i<p;i++)
	{
		ans[i]=(ans[i]+p1)%p1;
		printf("%lld\n",ans[i]);
	}
	return 0;
}
