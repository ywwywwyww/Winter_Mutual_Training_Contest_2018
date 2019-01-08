#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll p=19491001;
const int N=500010;
ll inv[N],fac[N],ifac[N];
ll fp(ll a,ll b)
{
	a%=p;
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
void init(int x)
{
	inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=x;i++)
	{
		inv[i]=-p/i*inv[p%i]%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
}
ll binom(int x,int y)
{
	return x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0;
}
int n,k,d;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("uoj450.in","r",stdin);
	freopen("uoj450.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&k,&d);
	if(d==1)
	{
		printf("%lld\n",fp(k,n));
		return 0;
	}
	init(k);
	if(d==2)
	{
		ll ans=0;
		for(int i=0;i<=k;i++)
			ans=(ans+binom(k,i)*fp(2*i-k,n))%p;
		ans=ans*fp(fp(2,k),p-2)%p;
		ans=(ans%p+p)%p;
		printf("%lld\n",ans);
		return 0;
	}
	const ll w=663067;
	ll ans=0;
	for(int i=0;i<=k;i++)
		for(int j=0;i+j<=k;j++)
			ans=(ans+binom(k,i)*binom(k-i,j)%p*fp(i+j*w+(k-i-j)*w%p*w,n))%p;
	ans=ans*fp(fp(3,k),p-2)%p;
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
