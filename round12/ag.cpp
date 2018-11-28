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
int a[1000100];
int main()
{
	freopen("a.in","w",stdout);
	srand(time(0));
	for(int i=1;i<=1000;i++)
		rand();
	int t=10;
	int n=10;
	int cnt;
	printf("%d\n",t);
	do
	{
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=rand()&1;
			cnt+=a[i];
		}
	}
	while(cnt<2);
	int v,s;
	do
	{
		v=rand()%n+1;
		s=0;
		for(int i=1;i<=v;i++)
			s+=a[i];
	}
	while(s==0||s==cnt);
	for(int i=1;i<=n;i++)
		if(a[i])
			if(i<=v)
				putchar('W');
			else
				putchar('B');
		else
			putchar('.');
	printf("\n");
	return 0;
}
