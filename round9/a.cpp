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
namespace flow
{
	int h[N];
	int v[N];
	int c[N];
	int t[N];
	int u[N];
	int b[N];
	int cnt;
	int f[N];
	void init()
	{
		cnt=0;
		memset(h,0,sizeof h);
		memset(b,0,sizeof b);
		memset(f,0,sizeof f);
		memset(v,0,sizeof v);
		memset(c,0,sizeof c);
		memset(u,0,sizeof u);
		memset(t,0,sizeof t);
	}
	void add(int x,int y,int z,int _)
	{
		cnt++;
		u[cnt]=x;
		v[cnt]=y;
		c[cnt]=z;
		b[cnt]=_;
		t[cnt]=h[x];
		h[x]=cnt;
	}
	int q[N];
	int head,tail;
	int S,T;
	int op(int x)
	{
		return ((x-1)^1)+1;
	}
	int solve(int s)
	{
		int ans=0;
		while(ans<s)
		{
			memset(f,0,sizeof f);
			head=1;
			tail=0;
			q[++tail]=S;
			while(tail>=head)
			{
				int x=q[head++];
				for(int i=h[x];i;i=t[i])
					if(c[i]&&!f[v[i]])
					{
						f[v[i]]=i;
						q[++tail]=v[i];
					}
			}
			if(!f[T])
				return ans;
			ans++;
			for(int i=f[T];;i=f[u[i]])
			{
				c[i]--;
				c[op(i)]++;
				if(u[i]==S)
					break;
			}
		}
		return ans;
	}
}
void add(int x,int y,int z)
{
	flow::add(x,y,z,1);
	flow::add(y,x,0,0);
}
using flow::S;
using flow::T;
int n,m;
int lx[N],ly[N];
int x1,x2,x3;
int t;
int a[4][N];
int t2;
int b[4][N];
int c[N],d[N];
vector<int> ans;
void output()
{
	printf("%d\n",(int)ans.size()-1);
	for(auto v:ans)
		printf("%d ",v);
}
int gao(int x,int y)
{
	if(x<y)
		swap(x,y);
	if(!y)
	{
		return x==1?2:1;
	}
	if(x==y)
		return x==1?2:1;
	return x^y;
}
int check(int c1,int c2,int d1,int d2)
{
	if(!d1)
		return 0;
	if(!d2)
		return 1;
	if(c1==c2&&d1>d2)
		return 1;
	return 0;
}
int main()
{
	open("a");
	scanf("%d%d",&n,&m);
	scanf("%d%d%d",&x1,&x2,&x3);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&lx[i],&ly[i]);
	for(int i=1;i<=n;i++)
		add(i,i+n,1);
	for(int i=1;i<=m;i++)
	{
		add(lx[i]+n,ly[i],1);
		add(ly[i]+n,lx[i],1);
	}
	S=x1+n;
	T=x2;
	flow::solve(3);
	for(int i=flow::h[S];i;i=flow::t[i])
		if(!flow::c[i]&&flow::b[i]&&t<3)
		{
			t++;
			for(int j=flow::v[i];j!=T;)
			{
				if(j<=n)
				{
					a[t][++a[t][0]]=j;
					c[j]=t;
					d[j]=a[t][0];
				}
				for(int k=flow::h[j];k;k=flow::t[k])
					if(!flow::c[k]&&flow::b[k])
					{
						j=flow::v[k];
						break;
					}
			}
		}
	c[x1]=c[x2]=1;
	d[x1]=0;
	d[x2]=a[1][0]+1;
	if(c[x3])
	{
		ans.push_back(x1);
		for(int i=1;i<=a[c[x3]][0];i++)
			ans.push_back(a[c[x3]][i]);
		ans.push_back(x2);
		int v=(c[x3]==1?2:1);
		for(int i=a[v][0];i>=1;i--)
			ans.push_back(a[v][i]);
		ans.push_back(x1);
		output();
		return 0;
	}
	flow::init();
	for(int i=1;i<=n;i++)
		if(i!=x1&&i!=x2&&!c[i])
			add(i,i+n,1);
	for(int i=1;i<=m;i++)
	{
		add(lx[i]+n,ly[i],1);
		add(ly[i]+n,lx[i],1);
	}
	S=x3+n;
	T=2*n+1;
	add(x1,T,1);
	add(x2,T,1);
	for(int i=1;i<=3;i++)
		for(int j=1;j<=a[i][0];j++)
			add(a[i][j],T,1);
	if(flow::solve(2)<2)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=flow::h[S];i;i=flow::t[i])
		if(!flow::c[i]&&flow::b[i]&&t2<2)
		{
			t2++;
			for(int j=flow::v[i];j!=T;)
			{
				if(j<=n)
					b[t2][++b[t2][0]]=j;
				for(int k=flow::h[j];k;k=flow::t[k])
					if(!flow::c[k]&&flow::b[k])
					{
						j=flow::v[k];
						break;
					}
			}
		}
	int c1=c[b[1][b[1][0]]];
	int c2=c[b[2][b[2][0]]];
	int d1=d[b[1][b[1][0]]];
	int d2=d[b[2][b[2][0]]];
	b[1][0]--;
	b[2][0]--;
	if(check(c1,c2,d1,d2))
	{
		swap(c1,c2);
		swap(d1,d2);
		swap(b[1],b[2]);
	}
	int v=gao(c1,c2);
	ans.push_back(x1);
	for(int i=1;i<=d1;i++)
		ans.push_back(a[c1][i]);
	for(int i=b[1][0];i>=1;i--)
		ans.push_back(b[1][i]);
	ans.push_back(x3);
	for(int i=1;i<=b[2][0];i++)
		ans.push_back(b[2][i]);
	for(int i=d2;i<=a[c2][0];i++)
		ans.push_back(a[c2][i]);
	ans.push_back(x2);
	for(int i=a[v][0];i>=1;i--)
		ans.push_back(a[v][i]);
	ans.push_back(x1);
	output();
	return 0;
}
