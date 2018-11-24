#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll p=998244353;
ll fac[5010],ifac[5010],inv[5010];
ll f[60][5010];
ll g[110][110];
int a[60];
int n;
int s[60];
ll c[110][110];
ll c1[110],c2[110];
ll binom(int x,int y)
{
    return x>=y&&y>=0?fac[x]*ifac[y]%p*ifac[x-y]%p:0;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("c.in","r",stdin);
    freopen("c3.out","w",stdout);
#endif
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];
    }
    inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1;
    for(int i=2;i<=5000;i++)
    {
        inv[i]=-p/i*inv[p%i]%p;
        fac[i]=fac[i-1]*i%p;
        ifac[i]=ifac[i-1]*inv[i]%p;
    }
    g[0][0]=1;
    for(int i=1;i<=100;i++)
        for(int j=1;j<=100;j++)
            for(int k=1;k<=i;k++)
                g[i][j]=(g[i][j]+g[i-k][j-1]*k)%p;
    f[0][0]=1;
    for(int i=1;i<n;i++)
        for(int j=1;j<=a[i];j++)
            for(int k=1;k<=j;k++)
                c[i][k]=(c[i][k]+g[a[i]][j]*binom(j-1,k-1)%p*((j-k)&1?-1:1))%p;
    for(int i=n;i<=n;i++)
        for(int j=1;j<=a[i];j++)
            for(int k=1;k<=j;k++)
                c1[k]=(c1[k]+g[a[i]][j]*binom(j-1,k-1)%p*((j-k)&1?-1:1))%p;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=a[i];j++)
            for(int k=0;k<=s[i-1];k++)
                f[i][k+j]=(f[i][k+j]+f[i-1][k]*c[i][j]%p*binom(k+j,k))%p;
    ll ans=0;
    for(int j=1;j<=a[n];j++)
        for(int k=0;k<=s[n-1];k++)
            ans=(ans+f[n-1][k]*c1[j]%p*binom(k+j,k))%p;
    ans=ans%p;
    ans=(ans+p)%p;
    printf("%lld\n",ans);
    return 0;
}
