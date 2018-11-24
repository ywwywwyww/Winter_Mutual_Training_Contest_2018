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
int n;
int a1[N],a2[N];
int t;
int main()
{
	open("c");
	scanf("%d",&n);
	if(n%5==1||n%5==2)
	{
		t=n/5*2;
		for(int i=1;i<=t;i++)
			a1[i]=i;
		a2[1]=t+1;
		for(int i=2;i<=t/2+1;i++)
			a2[i]=t/2*3+i-1;
		for(int i=t/2+2;i<=t;i++)
			a2[i]=t/2+i;
	}
	else
	{
		t=(n-1)/5*2+1;
		for(int i=1;i<=t;i++)
			a1[i]=i;
		for(int i=t/2+2;i<=t;i++)
			a2[i]=i+t/2;
		for(int i=1;i<=t/2+1;i++)
			a2[i]=i+t+t/2;
	}
	printf("%d\n",t);
	for(int i=1;i<=t;i++)
		printf("%d %d\n",a1[i],a2[i]);
	return 0;
}
