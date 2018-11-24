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
const int N=50;
int x[N],y[N];
int n;
ll f[2][1010][2010];
ll gao()
{
	memset(f,0,sizeof f);
	f[0][1000][1000]=1;
	for(int i=0;i<n;i++)
	{
		memset(f[(i&1)^1],0,sizeof f[(i&1)^1]);
		for(int j=0;j<=1000;j++)
			for(int k=0;k<=2000;k++)
				if(f[i&1][j][k])
				{
					f[(i&1)^1][min(j+x[i+1],1000)][k+x[i+1]]+=f[i&1][j][k];
					f[(i&1)^1][min(min(j,k-y[i+1]),1000)][k+x[i+1]-y[i+1]]+=f[i&1][j][k];
				}
	}
	ll ans=0;
	for(int i=0;i<1000;i++)
		for(int j=0;j<=2000;j++)
			ans+=f[n&1][i][j];
	return ans;
}
int main()
{
	open("b");
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&x[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&y[i]);
	ll ans=1ll<<n;
	ans-=gao();
	for(int i=1;i<=n;i++)
		swap(x[i],y[i]);
	ans-=gao();
	printf("%lld\n",ans);
	return 0;
}
