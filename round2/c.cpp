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
const int N=1000010;
ll n,m;
ll h,p;
ll A,B,C;
ll f[N];
ll S_hb[N];
ll S_b[N];
ll T_b[N];
ll inv[N];
ll fp(ll a,ll b)
{
	a%=p;
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
namespace init
{
	void gao()
	{	
		inv[1]=1;
		for(int i=2;i<=n+5;i++)
			inv[i]=(-p/i*inv[p%i]%p+p)%p;
		if(B==0)
		{
			for(int i=0;i<=n;i++)
			{
				S_b[i]=1;
				T_b[i]=m;
			}
		}
		else if(B==1)
		{
			S_b[0]=m;
			T_b[0]=(m+1)*m%p*inv[2]%p;
			for(int i=1;i<=n;i++)
			{
				S_b[i]=S_b[i-1]*(m+i)%p*inv[i+1]%p;
				T_b[i]=T_b[i-1]*(m+i+1)%p*inv[i+2]%p;
			}
		}
		else
		{
			ll _inv=fp(B-1,p-2);
			S_b[0]=(fp(B,m)-1)*_inv%p;
			T_b[0]=(B*S_b[0]-m)%p*_inv%p;
			ll pw=fp(B,m);
			ll s=1;
			for(int i=1;i<=n;i++)
			{
				s=s*(m+i-1)%p*inv[i]%p;
				S_b[i]=(s*pw-S_b[i-1])%p*_inv%p;
				T_b[i]=(B*S_b[i]-T_b[i-1])%p*_inv%p;
			}
		}
		if(h*B==0)
		{
			for(int i=0;i<=n;i++)
				S_hb[i]=1;
		}
		else if(h*B==1)
		{
			S_hb[0]=m;
			for(int i=1;i<=n;i++)
				S_hb[i]=S_hb[i-1]*(m+i)%p*inv[i+1]%p;
		}
		else
		{
			ll _inv=fp(h*B-1,p-2);
			S_hb[0]=(fp(h*B,m)-1)*_inv%p;
			ll pw=fp(h*B,m);
			ll s=1;
			for(int i=1;i<=n;i++)
			{
				s=s*(m+i-1)%p*inv[i]%p;
				S_hb[i]=(s*pw-S_hb[i-1])%p*_inv%p;
			}
		}
	}
}
namespace gao1
{
	
	ll pw_h_m_A[N];
	ll pw_h_m[N];
	ll gao()
	{
		ll res=0;
		ll s=0;
		ll h_m=fp(h,m);
		pw_h_m_A[0]=pw_h_m[0]=1;
		for(int i=1;i<=n;i++)
		{
			pw_h_m_A[i]=pw_h_m_A[i-1]*h_m%p*A%p;
			pw_h_m[i]=pw_h_m[i-1]*h_m%p;
		}
		for(int i=n;i>=1;i--)
		{
			s=(s+pw_h_m_A[n-i]*S_hb[n-i])%p;
			res=(res+f[i]*B%p*pw_h_m[i-1]%p*s)%p;
		}
		return res;
	}
}
namespace gao2
{
	ll pw_A[N];
	ll pw_h_m_A[N];
	ll pw_h_m[N];
	ll gao()
	{
		if(!C)
			return 0;
		ll res=0;
		ll h_m=fp(h,m);
		ll invh_1=fp(h-1,p-2);
		if(h==1)
		{
			pw_A[0]=1;
			for(int i=1;i<=n;i++)
				pw_A[i]=pw_A[i-1]*A%p;
			for(int i=0;i<n;i++)
				res=(res+pw_A[i]*(n-i)%p*T_b[i])%p;
		}
		else
		{
			pw_h_m_A[0]=pw_h_m[0]=1;
			for(int i=1;i<=n;i++)
			{
				pw_h_m_A[i]=pw_h_m_A[i-1]*h_m%p*A%p;
				pw_h_m[i]=pw_h_m[i-1]*h_m%p;
			}
			for(int i=0;i<n;i++)
				res=(res+pw_h_m_A[i]*(pw_h_m[n-i]-1)%p*fp(h_m-1,p-2)%p*((h_m*S_b[i]-S_hb[i])%p)%p*invh_1)%p;
		}
		return res*C%p;
	}
}
int main()
{
	open("c");
	rd();
	scanf("%lld%lld%lld%lld",&n,&m,&h,&p);
	scanf("%lld%lld%lld",&A,&B,&C);
	for(int i=1;i<=n;i++)
		f[i]=rd();
	if(!h)
	{
		printf("%lld\n",(B*f[1]+C)%p);
		return 0;
	}
	init::gao();
	ll ans1=gao1::gao();
	ll ans2=gao2::gao();
	ll ans=((ans1+ans2)%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
