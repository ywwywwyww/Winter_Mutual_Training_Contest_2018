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
const int N=100010;
int n;
struct zjtakioi2019
{
	int t[500000];
	int s[500000];
	int s2[500000];
	#define lc (p<<1)
	#define rc ((p<<1)|1)
	#define mid ((L+R)>>1)
	void add(int p,int l,int r,int v,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			t[p]+=v;
			s[p]+=v;
			return;
		}
		if(l<=mid)
			add(lc,l,r,v,L,mid);
		if(r>mid)
			add(rc,l,r,v,mid+1,R);
		s[p]=min(s[lc],s[rc])+t[p];
	}
	int get(int p,int x,int L,int R)
	{
		if(L==R)
			return t[p];
		if(x<=mid)
			return get(lc,x,L,mid)+t[p];
		else
			return get(rc,x,mid+1,R)+t[p];
	}
	int query(int p,int v,int L,int R)
	{
		if(L==R)
			return L;
		v-=t[p];
		if(s[lc]<=v)
			return query(lc,v,L,mid);
		return query(rc,v,mid+1,R);
	}
	void update(int p,int x,int v,int L,int R)
	{
		if(L==R)
		{
			s2[p]=v;
			return;
		}
		if(x<=mid)
			update(lc,x,v,L,mid);
		else
			update(rc,x,v,mid+1,R);
		s2[p]=min(s2[lc],s2[rc]);
	}
	int query2(int p,int l,int r,int v,int L,int R)
	{
		if(l<=L&&r>=R&&s2[p]>v)
			return 0;
		if(L==R)
			return L;
		if(l<=mid&&s2[lc]<=v)
		{
			int res=query2(lc,l,r,v,L,mid);
			if(res)
				return res;
		}
		return query2(rc,l,r,v,mid+1,R);
	}
	#undef mid
	int a[N];
	int t1,t2;
	int a1[N],a2[N];
	//1:max
	//2:min
	int c[N];
	zjtakioi2019()
	{
		t1=t2=0;
		a1[0]=a2[0]=0;
	}
	void gao()
	{
		for(int i=1;i<=n;i++)
		{
			while(t1&&a[a1[t1]]<a[i])
			{
				add(1,a1[t1-1]+1,a1[t1],-a[a1[t1]],1,n);
				t1--;
			}
			add(1,a1[t1]+1,i,a[i],1,n);
			a1[++t1]=i;
			while(t2&&a[a2[t2]]>a[i])
			{
				add(1,a2[t2-1]+1,a2[t2],a[a2[t2]],1,n);
				t2--;
			}
			add(1,a2[t2]+1,i,-a[i],1,n);
			a2[++t2]=i;
			if(i>1)
				add(1,1,i-1,-1,1,n);
			c[i]=query(1,0,1,n);
			update(1,i,c[i],1,n);
		}
	}
	int query(int l,int r)
	{
		return query2(1,r,n,l,1,n);
	}
}
s1,s2;
int a[N];
int q,type;
int main()
{
	open("b");
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		a[i]=rd();
		s1.a[i]=a[i];
		s2.a[n-i+1]=a[i];
	}
	s1.gao();
	s2.gao();
	int ansl=0,ansr=0;
	scanf("%d%d",&q,&type);
	int l,r;
	for(int i=1;i<=q;i++)
	{
		l=rd();
		r=rd();
		l^=type*ansl;
		r^=type*ansr;
		ansr=s1.query(l,r);
		ansl=n-s2.query(n-r+1,n-l+1)+1;
		printf("%d %d\n",ansl,ansr);
	}
	return 0;
}
