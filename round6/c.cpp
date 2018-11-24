#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<map>
using namespace std;
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
const int N=100010;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
map<int,int> f[11];
int a[N];
int b[N];
char str[30];
int m,n;
ll s;
ll g[N][30];
int main()
{
	open("c");
	scanf("%s",str);
	m=strlen(str);
	int o=0;
	for(int i=0;i<m;i++)
		o|=((str[i]-'0')^1)<<i;
	scanf("%d",&n);
	s=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		s=s*fp(a[i],b[i]-1)%p;
	}
	sort(a+1,a+n+1);
	int q=0;
	while(q<n&&a[q+1]<=m)
		q++;
	f[0][0]=1;
	for(int i=0;i<q;i++)
	{
		ll y=0;
		for(int j=0;j<m+a[i+1];j+=a[i+1])
			y|=1ll<<j;
		for(auto v:f[i])
			for(int j=0;j<a[i+1];j++)
			{
				ll z=(v.first|(y<<j))&((1<<m)-1);
				if((z|o)==o)
					(f[i+1][z]+=v.second)%=p;
			}
	}
	for(auto v:f[q])
		(g[0][__builtin_popcount(v.first)]+=v.second)%=p;
	int cnt=0;
	for(int i=0;i<m;i++)
		cnt+=(str[i]-'0')^1;
	for(int i=0;i<n-q;i++)
		for(int j=0;j<=cnt;j++)
		{
			g[i+1][j]=(g[i+1][j]+g[i][j]*(a[i+q+1]-m+j))%p;
			g[i+1][j+1]=(g[i+1][j+1]+g[i][j]*(cnt-j))%p;
		}
	ll ans=g[n-q][cnt]*s%p;
	printf("%lld\n",ans);
	return 0;
}
