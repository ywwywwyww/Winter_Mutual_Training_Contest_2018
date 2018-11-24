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
vector<pii> ans;
int t=2;
int a[100][100];
void gen(int x)
{
	int last=1;
	for(int i=1;i<=x;i++)
	{
		t++;
		a[t][last]=a[last][t]=1;
		ans.push_back(pii(last,t));
		last=t;
	}
	a[last][2]=a[2][last]=1;
	ans.push_back(pii(2,last));
}
int main()
{
	freopen("a.in","w",stdout);
	srand(time(0));
	for(int i=1;i<=1000;i++)
		rand();
	int n=10;
	for(int i=1;i<=3;i++)
		gen(rand()%2+1);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		do
		{
			x=rand()%n+1;
			y=rand()%n+1;
		}
		while(!(!a[x][y]&&x!=y));
		a[x][y]=a[y][x]=1;
		ans.push_back(pii(x,y));
	}
	int x;
	do
	{
		x=rand()%n+1;
	}
	while(x<=2);
	printf("%d %d\n%d %d %d\n",n,(int)ans.size(),1,2,x);
	for(auto v:ans)
		printf("%d %d\n",v.first,v.second);
	return 0;
}
