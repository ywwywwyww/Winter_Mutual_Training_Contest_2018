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
const int N=100;
int n;
int a[N];
int b[N];
int d[N];
int c[N];
int ans;
void dfs(int x,int s)
{
	if(s+(n-x+1)/2<ans)
		return;
	if(x>n)
	{
		if(s>ans)
		{
			ans=s;
			for(int i=1;i<=n;i++)
				c[i]=a[i];
		}
		return;
	}
	a[x]=x;
	dfs(x+1,s);
	if(d[x])
		return;
	for(int i=x+1;i<=n;i++)
		if(!d[i]&&x+i<=n&&!b[x+i])
		{
			b[x+i]=1;
			d[i]=1;
			a[x]=i;
			a[i]=x;
			dfs(x+1,s+1);
			d[i]=0;
			b[x+i]=0;
		}
}
int main()
{
//	freopen("c.in","r",stdin);
//	freopen("c2.out","w",stdout);
	scanf("%d",&n);
	memset(b,0,sizeof b);
	dfs(1,0);
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		if(c[i]>i)
			printf("%d %d\n",i,c[i]);
	return 0;
}
