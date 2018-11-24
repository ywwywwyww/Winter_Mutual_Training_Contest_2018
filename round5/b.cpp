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
int a[N];
int n,q;
int s[N];
int f[N];
int main()
{
	open("b");
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		a[i]=rd();
		s[i]=s[i-1]+a[i];
	}
	for(int i=1;i<n;i++)
		for(int j=s[i-1]+1;j<=s[i];j++)
			f[j]=(s[i-1]-(j-s[i-1])<0?j-s[i-1]-s[i-1]:f[s[i-1]-(j-s[i-1])]);
	scanf("%d",&q);
	int x;
	while(q--)
	{
		scanf("%d",&x);
		if(x>s[n-1])
			printf("%d ",x-s[n-1]);
		else
			printf("%d ",f[s[n-1]-x]);
	}
	return 0;
}
