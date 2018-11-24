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
int b[N][N];
int ax[N*N];
int ay[N*N];
int t;
int n,m;
int main()
{
	freopen("a.in","r",stdin);
	freopen("a2.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[j][i]=(get()=='*');
	swap(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j])
			{
				t++;
				ax[t]=i;
				ay[t]=j;
			}
	int tot=n*(m-1)+m*(n-1);
	ll ans=0;
	for(int i=1;i<1<<t;i++)
	{
		for(int j=1;j<=t;j++)
			b[ax[j]][ay[j]]=(i>>(j-1))&1;
		int s=0;
		for(int j=1;j<=t;j++)
			if((i>>(j-1))&1)
			{
				if(ax[j]<n)
					s++;
				if(ay[j]<m)
					s++;
				if(ax[j]>1&&!b[ax[j]-1][ay[j]])
					s++;
				if(ay[j]>1&&!b[ax[j]][ay[j]-1])
					s++;
			}
		ans=(ans+fp(s,p-2)*tot%p*(__builtin_popcount(i)&1?1:-1))%p;
	}
	ans=(ans+p)%p;
	printf("%lld\n",ans);
	return 0;
}
