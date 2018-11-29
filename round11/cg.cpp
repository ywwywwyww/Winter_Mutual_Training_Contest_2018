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
int a1[100010],a2[100010];
int x1[100010],y1[100010];
int x2[100010],y2[100010];
int main()
{
	srand(time(0));
	freopen("c.in","w",stdout);
	for(int i=1;i<=1000;i++)
		rand();
	int H=1000;
	int W=1000;
	printf("%d %d\n",H,W);
	int n=100;
	for(int i=0;i<=n+1;i++)
	{
		do
		{
			x1[i]=rand()%H+1;
		}
		while(a1[x1[i]]);
		a1[x1[i]]=1;
		do
		{
			y1[i]=rand()%W+1;
		}
		while(a2[y1[i]]);
		a2[y1[i]]=1;
	}
	sort(x1,x1+n+2);
	sort(y1,y1+n+2);
	x1[n+2]=H+1;
	y1[n+2]=W+1;
	printf("%d\n",n);
	for(int i=0;i<=n+1;i++)
	{
		x2[i]=x1[i]+rand()%(x1[i+1]-x1[i]);
		y2[i]=y1[i]+rand()%(y1[i+1]-y1[i]);
		printf("%d %d %d %d\n",x1[i],y1[i],x2[i],y2[i]);
	}
	return 0;
}
