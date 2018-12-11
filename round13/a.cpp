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
vector<int> g[N];
int s[N],f[N],d[N],ms[N],e[N],w[N],t[N],b[N],ti,ed[N];
void dfs(int x,int fa,int dep)
{
	s[x]=1;
	f[x]=fa;
	d[x]=dep;
	for(auto v:g[x])
		if(v!=fa)
		{
			dfs(v,x,dep+1);
			s[x]+=s[v];
			if(s[v]>s[ms[x]])
				ms[x]=v;
		}
}
void dfs2(int x,int top)
{
	w[x]=++ti;
	e[ti]=x;
	t[x]=top;
	if(ms[x])
	{
		dfs2(ms[x],top);
		b[x]=b[ms[x]];
	}
	else
		b[x]=x;
	for(auto v:g[x])
		if(v!=f[x]&&v!=ms[x])
			dfs2(v,v);
	ed[x]=ti;
}
int n,m,type;
int a[N];
namespace bit
{
	int a[N];
	void add(int x,int v)
	{
		for(;x<=n;x+=x&-x)
			a[x]+=v;
	}
	int query(int x)
	{
		int s=0;
		for(;x;x-=x&-x)
			s+=a[x];
		return s;
	}
}
struct block
{
	int st;
	int len;
	int cnt;
	pii *a;
	pii *b;
	int cur;
	int t;
	int ans;
	void init()
	{
		a=new pii[len+1];
		b=new pii[len+1];
		for(int i=1;i<=len;i++)
			a[i]=pii(::a[st+i-1],i);
		sort(a+1,a+len+1);
		cnt=0;
		t=0;
		for(int i=1;i<=len;i++)
			if(!cnt||a[i].first!=b[cnt].first)
			{
				cnt++;
				b[cnt].first=a[i].first;
				b[cnt].second=1;
			}
			else
				b[cnt].second++;
		b[0].first=-0x3fffffff;
		ans=0;
		for(int i=cnt;i>=0;i--)
			if(b[i].first>0)
				ans+=b[i].second;
			else
			{
				cur=i;
				break;
			}
	}
	void add(int v)
	{
		t+=v;
		if(v==1)
		{
			if(cur&&b[cur].first+t>0)
			{
				ans+=b[cur].second;
				cur--;
			}
		}
		else
		{
			if(cur<cnt&&b[cur+1].first+t<=0)
			{
				cur++;
				ans-=b[cur].second;
			}
		}
	}
	void push()
	{
		for(int i=1;i<=len;i++)
			::a[st+i-1]+=t;
		for(int i=1;i<=len;i++)
			a[i].first+=t;
		for(int i=1;i<=cnt;i++)
			b[i].first+=t;
		t=0;
	}
	static pii a1[],a2[];
	void add(int l,int r,int v)
	{
		int t1=0,t2=0;
		for(int i=1;i<=len;i++)
			if(a[i].second>=l&&a[i].second<=r)
			{
				::a[a[i].second+st-1]+=v;
				a1[++t1]=pii(::a[a[i].second+st-1],a[i].second);
			}
			else
				a2[++t2]=pii(::a[a[i].second+st-1],a[i].second);
		merge(a1+1,a1+t1+1,a2+1,a2+t2+1,a+1);
		
		cnt=0;
		for(int i=1;i<=len;i++)
			if(!cnt||a[i].first!=b[cnt].first)
			{
				cnt++;
				b[cnt].first=a[i].first;
				b[cnt].second=1;
			}
			else
				b[cnt].second++;
		b[0].first=-0x3fffffff;
		ans=0;
		for(int i=cnt;i>=0;i--)
			if(b[i].first>0)
				ans+=b[i].second;
			else
			{
				cur=i;
				break;
			}
	}
};
pii block::a1[N],block::a2[N];
struct zjtakioi2019
{
	int st;
	int tot;
	int num;
	int size;
	int ans;
	block *a;
	void build(int x,int len)
	{
		st=w[x];
		tot=len;
		size=ceil(sqrt(len));
		num=(len+size-1)/size;
		a=new block[num+1];
		for(int i=1;i<=num;i++)
		{
			a[i].st=st+(i-1)*size;
			a[i].len=min(i*size,len)-(i-1)*size;
			a[i].init();
			ans+=a[i].ans;
		}
		bit::add(st,ans);
	}
	void add(int l,int r,int v)
	{
		bit::add(st,-ans);
		int bl=(l-1)/size+1;
		int br=(r-1)/size+1;
		if(bl==br)
		{
			a[bl].push();
			ans-=a[bl].ans;
			a[bl].add(l-(bl-1)*size,r-(bl-1)*size,v);
			ans+=a[bl].ans;
		}
		else
		{
			a[bl].push();
			ans-=a[bl].ans;
			a[bl].add(l-(bl-1)*size,a[bl].len,v);
			ans+=a[bl].ans;
			a[br].push();
			ans-=a[br].ans;
			a[br].add(1,r-(br-1)*size,v);
			ans+=a[br].ans;
			for(int i=bl+1;i<br;i++)
			{
				ans-=a[i].ans;
				a[i].add(v);
				ans+=a[i].ans;
			}
		}
		bit::add(st,ans);
	}
	int query(int l,int r)
	{
		int res=0;
		int bl=(l-1)/size+1;
		int br=(r-1)/size+1;
		if(bl==br)
		{
			a[bl].push();
			for(int i=l;i<=r;i++)
				res+=(::a[st+i-1]>0);
		}
		else
		{
			a[bl].push();
			for(int i=l;i<=bl*size;i++)
				res+=(::a[st+i-1]>0);
			a[br].push();
			for(int i=(br-1)*size+1;i<=r;i++)
				res+=(::a[st+i-1]>0);
			for(int i=bl+1;i<br;i++)
				res+=a[i].ans;
		}
		return res;
	}
}
c[N];
void modify(int x,int y,int v)
{
	while(t[x]!=t[y])
		if(d[t[x]]>d[t[y]])
		{
			c[t[x]].add(1,w[x]-w[t[x]]+1,v);
			x=f[t[x]];
		}
		else
		{
			c[t[y]].add(1,w[y]-w[t[y]]+1,v);
			y=f[t[y]];
		}
	if(w[x]<=w[y])
		c[t[x]].add(w[x]-w[t[x]]+1,w[y]-w[t[y]]+1,v);
	else
		c[t[x]].add(w[y]-w[t[y]]+1,w[x]-w[t[x]]+1,v);
}
int chain_query(int x,int y)
{
	int res=0;
	while(t[x]!=t[y])
		if(d[t[x]]>d[t[y]])
		{
			res+=c[t[x]].query(1,w[x]-w[t[x]]+1);
			x=f[t[x]];
		}
		else
		{
			res+=c[t[y]].query(1,w[y]-w[t[y]]+1);
			y=f[t[y]];
		}
	if(w[x]<=w[y])
		res+=c[t[x]].query(w[x]-w[t[x]]+1,w[y]-w[t[y]]+1);
	else
		res+=c[t[x]].query(w[y]-w[t[y]]+1,w[x]-w[t[x]]+1);
	return res;
}
int subtree_query(int x)
{
	int res=0;
	res+=bit::query(ed[x])-bit::query(w[x]);
	res+=c[t[x]].query(w[x]-w[t[x]]+1,w[b[x]]-w[t[x]]+1);
	return res;
}
int main()
{
	open("a");
	scanf("%d%d%d",&n,&m,&type);
	int op,x,y,v;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0,1);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		a[w[i]]=x;
	}
	for(int i=1;i<=n;i++)
		if(t[i]==i)
			c[i].build(i,w[b[i]]-w[i]+1);
	int ans=0;
	c[1].query(1,1);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&x,&y,&v);
			x^=type*ans;
			y^=type*ans;
			modify(x,y,v);
		}
		else if(op==2)
		{
			scanf("%d%d",&x,&y);
			x^=type*ans;
			y^=type*ans;
			ans=chain_query(x,y);
			printf("%d\n",ans);
		}
		else
		{
			scanf("%d",&x);
			x^=type*ans;
			ans=subtree_query(x);
			printf("%d\n",ans);
		}
	}
	return 0;
}
