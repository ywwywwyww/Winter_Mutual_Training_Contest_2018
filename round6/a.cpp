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
using namespace std;
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
struct info
{
	int l,r,id;
};
info b[2*N];
int t;
map<int,int> c;
int a[N];
int s[N];
int ans[N];
int e[N];
int n,q;
void add(int x,int v)
{
	for(;x<=n;x+=x&-x)
		e[x]^=v;
}
int query(int x)
{
	int s=0;
	for(;x;x-=x&-x)
		s^=e[x];
	return s;
}
int main()
{
	open("a");
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		a[i]=rd();
		s[i]=s[i-1]^a[i];
	}
	int l,r;
	for(int i=1;i<=q;i++)
	{
		l=rd();
		r=rd();
		ans[i]=s[r]^s[l-1];
		t++;
		b[t].r=r;
		b[t].l=l;
		b[t].id=i;
		t++;
		b[t].r=l-1;
		b[t].l=l;
		b[t].id=i;
	}
	sort(b+1,b+t+1,[](info x,info y){return x.r<y.r;});
	for(int i=1,j=1;i<=n;i++)
	{
		while(j<=t&&b[j].r==0)
			j++;
		int last=c[a[i]];
		c[a[i]]=i;
		add(last+1,a[i]);
		for(;j<=t&&b[j].r==i;j++)
			ans[b[j].id]^=query(b[j].l);
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
