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
const ll p=1000000007;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
int n,m;
namespace gao1
{
	const int N=10000010;
	int f[N];
	int pw[N];
	bool b[N];
	int pri[N];
	int c[N];
	int cnt;
	void gao()
	{
		f[1]=1;
		pw[1]=1;
		for(int i=2;i<=n;i++)
		{
			if(!b[i])
			{
				pri[++cnt]=i;
				pw[i]=fp(i,m);
			}
			for(int j=1;j<=cnt&&i*pri[j]<=n;j++)
			{
				b[i*pri[j]]=1;
				pw[i*pri[j]]=(ll)pw[i]*pw[pri[j]]%p;
				if(i%pri[j]==0)
					break;
			}
		}
		for(int i=2;i<=n;i++)
		{
			if(!b[i])
			{
				c[i]=i;
				f[i]=fp(i,m+1)-fp(i-1,m+1);
			}
			for(int j=1;j<=cnt&&pri[j]<=i&&i*pri[j]<=n;j++)
			{
				int v=i*pri[j];
				if(i%pri[j]==0)
				{
					c[v]=c[i]*pri[j];
					if(c[v]==v)
						f[v]=((ll)pw[pri[j]]*f[i]+(ll)i*(pri[j]-1)*(pw[v]-pw[v-1]))%p;
					else
						f[v]=(ll)f[c[v]]*f[v/c[v]]%p;
					break;
				}
				c[v]=pri[j];
				f[v]=(ll)f[i]*f[pri[j]]%p;
			}
		}
		ll ans=0;
		for(int i=1;i<=n;i++)
			ans+=f[i];
		ans=(ans%p+p)%p;
		printf("%lld\n",ans);
	}
}
namespace gao2
{
	const int N=100010;
	ll inv[N],fac[N],ifac[N];
	ll binom(int x,int y)
	{
		return x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0;
	}
	int _;
	int b[N],pri[N],cnt;
	void init()
	{
		inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
		for(int i=2;i<=100000;i++)
		{
			inv[i]=-p/i*inv[p%i]%p;
			fac[i]=fac[i-1]*i%p;
			ifac[i]=ifac[i-1]*inv[i]%p;
		}
		for(int i=2;i<=_;i++)
		{
			if(!b[i])
				pri[++cnt]=i;
			for(int j=1;j<=cnt&&i*pri[j]<=_;j++)
			{
				b[i*pri[j]]=1;
				if(i%pri[j]==0)
					break;
			}
		}
	}
	ll pw[N],s[N];
	void init(int x)
	{
		pw[1]=1;
		for(int i=2;i<=x+2;i++)
		{
			if(!b[i])
				pw[i]=fp(i,x);
			for(int j=1;j<=cnt&&i*pri[j]<=n&&pri[j]<=i;j++)
			{
				pw[i*pri[j]]=pw[i]*pw[pri[j]]%p;
				if(i%pri[j]==0)
					break;
			}
		}
		for(int i=1;i<=x+2;i++)
			s[i]=(s[i-1]+pw[i])%p;
	}
	ll pre[N],suf[N];
	ll calc(int x,int y)
	{
		if(x<=y+2)
			return s[x];
		pre[0]=1;
		for(int i=1;i<=y+2;i++)
			pre[i]=pre[i-1]*(x-i)%p;
		suf[y+3]=1;
		for(int i=y+2;i>=1;i--)
			suf[i]=suf[i+1]*(x-i)%p;
		ll res=0;
		for(int i=1;i<=y+2;i++)
			res=(res+s[i]*pre[i-1]%p*suf[i+1]%p*ifac[i-1]%p*ifac[y+2-i]%p*((y+2-i)&1?-1:1))%p;
		return res;
	}
	ll s1[N],s2[N],ans1[N],ans2[N];
	void gao(int x)
	{
		init(x);
		calc(3,x);
		for(int i=1;i<=_;i++)
			s1[i]=(fp(i,x)+s1[i-1])%p;
		for(int i=1;n/i>_;i++)
			s2[i]=calc(n/i,x);
		for(int i=1;i<=cnt;i++)
		{
			ll v=fp(pri[i],x);
			int j;
			for(j=1;n/j/pri[i]>_&&n/j>=(ll)pri[i]*pri[i];j++)
				s2[j]=(s2[j]-v*(s2[j*pri[i]]-s1[pri[i]-1]))%p;
			for(;n/j>_&&n/j>=(ll)pri[i]*pri[i];j++)
				s2[j]=(s2[j]-v*(s1[n/j/pri[i]]-s1[pri[i]-1]))%p;
			for(j=_;j>=(ll)pri[i]*pri[i];j--)
				s1[j]=(s1[j]-v*(s1[j/pri[i]]-s1[pri[i]-1]))%p;
		}
	}
	ll g(int z,int x,int y)
	{
		if(z<0)
			return 0;
		return z==y?fp(x,(ll)y*m):fp(fp(x,y)-fp(x,y-z-1),m);
	}
	ll get(int x,int y)
	{
		ll res=0;
		for(int i=0;i<=y;i++)
			res=(res+fp(x,i)*(g(i,x,y)-g(i-1,x,y)))%p;
		return res;
	}
	ll solve(ll x,int y)
	{
		if(x<=1||x<pri[y])
			return 0;
		if(y>cnt)
			return (x<=_?ans1[x]:ans2[n/x])-ans1[_];
		ll res=(x<=_?ans1[x]:ans2[n/x])-ans1[pri[y]-1];
		for(int i=y;i<=cnt&&(ll)pri[i]*pri[i]<=x;i++)
		{
			ll x1=x/pri[i];
			for(int j=1;x1>=pri[i];j++,x1/=pri[i])
				res=(res+solve(x1,i+1)*get(pri[i],j)+get(pri[i],j+1))%p;
		}
		return res;
	}
	void gao()
	{
		_=sqrt(n)+0.5;
		init();
		for(int i=0;i<=m;i++)
		{
			gao(i);
			ll v=binom(m+1,i)*((m-i)&1?-1:1);
			for(int i=1;i<=_;i++)
				ans1[i]=(ans1[i]+v*s1[i])%p;
			for(int i=1;n/i>_;i++)
				ans2[i]=(ans2[i]+v*s2[i])%p;
		}
		ll ans=solve(n,1);
		ans++;
		ans=(ans%p+p)%p;
		printf("%lld\n",ans);
	}
}
int main()
{
	open("c");
	scanf("%d%d",&n,&m);
	if(n<=1e7)
		gao1::gao();
	else
		gao2::gao();
	return 0;
}
