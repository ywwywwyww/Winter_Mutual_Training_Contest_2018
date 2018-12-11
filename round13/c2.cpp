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
int n,m;
int a[1000],b[1000],c[1000],d[1000];
int gao(int v)
{
	if(v==19)
		int xxx=1;
	for(int i=1;i<=m;i++)
		b[i]=(v>>(i-1))&1;
	for(int i=1;i<=n;i++)
		c[i]=0;
	for(int i=1;i<=m;i++)
		d[i]=a[i];
	for(int t=0;;t++)
	{
		for(int i=1;i<=m;i++)
			c[d[i]]=1;
		if(*std::min_element(c+1,c+n+1))
			return t;
		for(int i=1;i<=m;i++)
			if(b[i])
			{
				d[i]++;
				if(d[i]>n)
					d[i]-=n;
			}
			else
			{
				d[i]--;
				if(d[i]<=0)
					d[i]+=n;
			}
	}
}
int main()
{
	freopen("c.in","r",stdin);
	freopen("c2.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	int ans=n;
	for(int i=0;i<1<<m;i++)
		ans=min(ans,gao(i));
	printf("%d\n",ans);
	return 0;
}
