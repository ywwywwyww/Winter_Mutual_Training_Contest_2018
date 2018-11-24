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
char get()
{
	char c;
	while((c=getchar())!='*'&&c!='.');
	return c;
}
const int N=110;
const ll p=998244353;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
int a[N][N];
int n,m;
ll f[N][7][1<<6][1210];
void add(ll &a,ll b)
{
	a=(a+b)%p;
}
int set(int x,int y,int v)
{
	x|=1<<(y-1);
	x^=(!v)<<(y-1);
	return x;
}
int main()
{
	open("a");
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[j][i]=(get()=='*');
	swap(n,m);
	int tot=n*(m-1)+m*(n-1);
	f[1][1][0][0]=-1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			for(int k=0;k<1<<m;k++)
				if(j==m)
				{
					int k1=set(k,j,0);
					for(int l=0;l<=2*n*m;l++)
						add(f[i+1][1][k1][l],f[i][j][k][l]);
					if(a[i][j])
					{
						int v=0;
						if(i<n)
							v++;
						if(j>1&&!((k>>(j-2))&1))
							v++;
						if(i>1&&!((k>>(j-1))&1))
							v++;
						int k2=set(k,j,1);
						for(int l=v;l<=2*n*m;l++)
							add(f[i+1][1][k2][l],-f[i][j][k][l-v]);
					}
				}
				else
				{
					int k1=set(k,j,0);
					for(int l=0;l<=2*n*m;l++)
						add(f[i][j+1][k1][l],f[i][j][k][l]);
					if(a[i][j])
					{
						int v=1;
						if(i<n)
							v++;
						if(j>1&&!((k>>(j-2))&1))
							v++;
						if(i>1&&!((k>>(j-1))&1))
							v++;
						int k2=set(k,j,1);
						for(int l=v;l<=2*n*m;l++)
							add(f[i][j+1][k2][l],-f[i][j][k][l-v]);
					}
				}
	}
	ll ans=0;
	for(int i=0;i<1<<m;i++)
		for(int j=1;j<=2*n*m;j++)
			ans=(ans+f[n+1][1][i][j]*tot%p*fp(j,p-2))%p;
	ans=(ans+p)%p;
	printf("%lld\n",ans);
	return 0;
}
