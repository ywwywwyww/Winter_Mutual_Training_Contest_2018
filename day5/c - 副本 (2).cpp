#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<map>
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
using std::map;
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
const int N=5000010;
map<int,int> s[N];
map<int,int> a[N];
int l[N];
int r[N];
int f[N];
int cnt;
char str[110][100];
int get(int x,int y)
{
	if(!s[x][y])
	{
		s[x][y]=++cnt;
		l[cnt]=x;
		r[cnt]=y;
	}
	return s[x][y];
}
int merge(int x,int y)
{
	if(x==y)
		return x;
	if(!x||!y)
		return x+y;
	if(a[x][y])
		return a[x][y];
	return a[x][y]=get(merge(l[x],l[y]),merge(r[x],r[y]));
}
int n,q;
int main()
{
	freopen("c.in","r",stdin);
	freopen("c2.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=q;i++)
		scanf("%s",str[i]+1);
	int rt=0;
	for(int i=1;i<=q;i++)
	{
		int now=get(0,0);
		for(int j=n;j>=1;j--)
			if(str[i][j]=='0')
				now=get(now,0);
			else if(str[i][j]=='1')
				now=get(0,now);
			else
				now=get(now,now);
		rt=merge(rt,now);
	}
	for(int i=1;i<=cnt;i++)
		if(!l[i]&&!r[i])
			f[i]=1;
		else
			f[i]=f[l[i]]+f[r[i]];
	printf("%d\n",f[rt]);
	return 0;
}
