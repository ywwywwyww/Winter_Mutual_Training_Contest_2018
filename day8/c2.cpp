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
const int N=200010;
ll inv[N],fac[N],ifac[N];
int a1[N],a2[N];
int n,m1,m2;
ll f[N],g[N];
ll binom(int x,int y)
{
	return x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0;
}
int main()
{
	freopen("c.in","r",stdin);
	freopen("c2.out","w",stdout);
	scanf("%d%d%d",&n,&m1,&m2);
	int x;
	for(int i=1;i<=m1;i++)
	{
		scanf("%d",&x);
		a1[x]=1;
	}
	for(int i=1;i<=m2;i++)
	{
		scanf("%d",&x);
		a2[x]=1;
	}
	a2[0]=1;
	inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++)
	{
		inv[i]=(-p/i*inv[p%i]%p+p)%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
	for(int i=1;i<=n;i++)
	{
		f[i]=a2[i-1];
		if(a1[0])
			f[i]=(f[i]+g[i-1])%p;
		for(int j=1;j<i;j++)
			if(a1[j])
				f[i]=(f[i]+g[i-j-1]*binom(i-1,j))%p;
		if(i>=2)
			g[i]=f[i];
		for(int j=2;j<i;j++)
			g[i]=(g[i]+g[i-j]*f[j]%p*binom(i-1,j-1))%p;
	}
	ll ans=f[n];
	ans=(ans+p)%p;
	printf("%lld\n",ans);
	return 0;
}
