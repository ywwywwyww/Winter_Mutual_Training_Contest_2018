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
ll c[2000000];
int a[100];
int f[100];
int lx[100],ly[100];
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}
int t;
int n,k;
int main()
{
	open("a");
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
		scanf("%d%d",&lx[i],&ly[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<1<<n;i++)
	{
		for(int j=1;j<=n;j++)
			f[j]=j;
		for(int j=1;j<n;j++)
			if(((i>>(lx[j]-1))&1)&&((i>>(ly[j]-1))&1))
				f[find(lx[j])]=find(ly[j]);
		int cnt=0;
		for(int j=1;j<=n;j++)
			if((i>>(j-1))&1)
				if(find(j)==j)
					cnt++;
		if(cnt>1)
			continue;
		ll s=0;
		for(int j=1;j<=n;j++)
			if((i>>(j-1))&1)
				s+=a[j];
		c[++t]=s;
	}
	sort(c+1,c+t+1);
	printf("%lld\n",c[k]);
	return 0;
}
