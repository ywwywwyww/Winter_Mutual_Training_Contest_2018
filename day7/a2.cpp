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
int n,m,s;
int a[N];
int f[1<<15][20][20];
int main()
{
	freopen("a.in","r",stdin);
	freopen("a2.out","w",stdout);
	scanf("%d%d%d",&n,&m,&s);
	if(m==0&&s!=1)
	{
		printf("-1\n");
		return 0;
	}
	if(m==n-1&&s!=n)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	memset(f,0x3f,sizeof f);
	f[1<<(s-1)][s][0]=0;
	for(int i=0;i<1<<n;i++)
		for(int j=1;j<=n;j++)
			if((i>>(j-1))&1)
				for(int k=1;k<=n;k++)
					if(!((i>>(k-1))&1))
					{
						if(i==28)
							int xxx=1;
						if(k<j)
							for(int l=0;l<n;l++)
								upmin(f[i|(1<<(k-1))][k][l+1],f[i][j][l]+a[j]-a[k]);
						else
							for(int l=0;l<=n;l++)
								upmin(f[i|(1<<(k-1))][k][l],f[i][j][l]+a[k]-a[j]);
					}
	int ans=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
		ans=min(ans,f[(1<<n)-1][i][m]);
	if(ans==0x3f3f3f3f)
		printf("-1\n");
	else
		printf("%d\n",ans);
	return 0;
}
