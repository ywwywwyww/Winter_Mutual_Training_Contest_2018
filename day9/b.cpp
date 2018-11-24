#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
//#include<cmath>
#include<vector>
#include<assert.h>
#include<set>
#include<queue>
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
using std::set;
using std::deque;
using std::multiset;
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

#ifdef DEBUG
//const int N=110;
const int N=100010;
#else
const int N=100010;
#endif

int Sx,Sy,Tx,Ty,x1[N],x2[N],y1[N],y2[N];
int dx[2*N],dy[2*N],tx,ty;
int down[2*N][3];
int n;
namespace init
{
	struct event
	{
		int x1,x2,y,c,id1,id2;
	};
	event a[10*N];
	int t;
	multiset<pii> s;
	int cmp(event a,event b)
	{
		return a.y>b.y;
	}
	void gao()
	{
		for(int i=1;i<=n;i++)
		{
			t++;
			a[t].y=y2[i];
			a[t].x1=x1[i];
			a[t].x2=x2[i];
			a[t].c=2;
			t++;
			a[t].x1=x1[i];
			a[t].y=y1[i];
			a[t].id1=i;
			a[t].id2=1;
			a[t].c=1;
			t++;
			a[t].x1=x2[i];
			a[t].y=y1[i];
			a[t].id1=i;
			a[t].id2=2;
			a[t].c=1;
		}
		t++;
		a[t].x1=Sx;
		a[t].y=Sy;
		a[t].id1=0;
		a[t].id2=1;
		a[t].c=1;
		t++;
		a[t].x1=Tx;
		a[t].y=Ty;
		a[t].id1=0;
		a[t].id2=2;
		a[t].c=1;
		sort(a+1,a+t+1,cmp);
		for(int i=1;i<=t;i++)
			if(a[i].c==2)
			{
				for(auto it=s.lower_bound(pii(a[i].x1+1,0));it!=s.end()&&it->first<a[i].x2;it=s.lower_bound(pii(a[i].x1+1,0)))
				{
					down[it->second/2][it->second%2+1]=a[i].y;
					s.erase(it);
				}
			}
			else
				s.insert(pii(a[i].x1,a[i].id1*2+a[i].id2-1));
	}
}

int nodecnt;
namespace graph
{
	int h[200*N];
	int v[1000*N];
	bool w[1000*N];
	int t[1000*N];
	int cnt;
	void add(int x,int y,int z)
	{
		cnt++;
		v[cnt]=y;
		w[cnt]=z;
		t[cnt]=h[x];
		h[x]=cnt;
	}
}
using graph::add;

namespace seg
{
	using graph::add;
	int s1[100*N];
	int s2[100*N];
	int t[100*N];
	#define lc (p<<1)
	#define rc ((p<<1)|1)
	#define mid ((L+R)>>1)
	void clear(int p)
	{
		s1[p]=s2[p]=0;
		t[p]=1;
	}
	void mt(int p)
	{
		if(!s1[lc]||!s1[rc])
			s1[p]=s1[lc]+s1[rc];
		else
		{
			s1[p]=++nodecnt;
			add(s1[p],s1[lc],0);
			add(s1[p],s1[rc],0);
		}
		
		if(!s2[lc]||!s2[rc])
			s2[p]=s2[lc]+s2[rc];
		else
		{
			s2[p]=++nodecnt;
			add(s2[lc],s2[p],0);
			add(s2[rc],s2[p],0);
		}
	}
	void push(int p)
	{
		if(t[p])
		{
			clear(lc);
			clear(rc);
			t[p]=0;
		}
	}
	void clear(int p,int l,int r,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			clear(p);
			return;
		}
		push(p);
		if(l<=mid)
			clear(lc,l,r,L,mid);
		if(r>mid)
			clear(rc,l,r,mid+1,R);
		mt(p);
	}
	void add(int p,int l,int r,int v,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			if(s1[p])
				add(v,s1[p],1);
			if(s2[p])
				add(s2[p],v,1);
			return;
		}
		push(p);
		if(l<=mid)
			add(lc,l,r,v,L,mid);
		if(r>mid)
			add(rc,l,r,v,mid+1,R);
	}
	void insert(int p,int x,int v,int L,int R)
	{
		if(L==R)
		{
			if(!s1[p])
				s1[p]=++nodecnt;
			if(!s2[p])
				s2[p]=++nodecnt;
			add(s1[p],v,0);
			add(v,s2[p],0);
			return;
		}
		push(p);
		if(x<=mid)
			insert(lc,x,v,L,mid);
		else
			insert(rc,x,v,mid+1,R);
		mt(p);
	}
}
int id(int x,int y)
{
	return x*4+y;
}
namespace build
{
	struct event
	{
		int y,x,v,c;
		event(int a=0,int b=0,int _=0,int d=0):y(a),x(b),v(_),c(d){}
	};
	event a[10*N];
	int t;
	int cmp(event a,event b)
	{
		if(a.y!=b.y)
			return a.y<b.y;
		return a.c<b.c;
	}
	set<int> st;
	void gao()
	{
		for(int i=1;i<=n;i++)
		{
			a[++t]=event(y1[i],x1[i],id(i,3),2);
			a[++t]=event(y2[i],x1[i],id(i,4),2);
			a[++t]=event(down[i][1],x1[i],id(i,1),1);
			a[++t]=event(down[i][2],x2[i],id(i,2),1);
			a[++t]=event(y1[i],0,i,10);
			a[++t]=event(y2[i],0,i,-10);
		}
		a[++t]=event(down[0][1],Sx,id(0,1),1);
		a[++t]=event(Sy,Sx,id(0,2),2);
		a[++t]=event(down[0][2],Tx,id(0,3),1);
		a[++t]=event(Ty,Tx,id(0,4),2);
		sort(a+1,a+t+1,cmp);
		st.insert(0);
		st.insert(t+1);
		nodecnt=4*n+4;
		for(int i=1;i<=t;i++)
			if(a[i].c==2)
			{
				int l=*(--(st.upper_bound(a[i].x)));
				int r=*(st.lower_bound(a[i].x));
				if(l==0)
					l++;
				if(r==t+1)
					r--;
				seg::add(1,l,r,a[i].v,1,t);
			}
			else if(a[i].c==1)
			{
				seg::insert(1,a[i].x,a[i].v,1,t);
			}
			else if(a[i].c==10)
			{
				int id=a[i].v;
				if(x1[id]+2<=x2[id])
					seg::clear(1,x1[id]+1,x2[id]-1,1,t);
				st.insert(x1[id]);
				st.insert(x2[id]);
			}
			else if(a[i].c==-10)
			{
				int id=a[i].v;
				st.erase(x1[id]);
				st.erase(x2[id]);
			}
	}
}
namespace bfs
{
	deque<int> q;
	int d[200*N];
	int b[200*N];
	int gao()
	{
		memset(d,0x3f,sizeof d);
		d[id(0,1)]=d[id(0,2)]=0;
		q.push_back(id(0,1));
		q.push_back(id(0,2));
		while(!q.empty())
		{
			int x=q.front();
			q.pop_front();
			if(b[x])
				continue;
			b[x]=1;
			for(int i=graph::h[x];i;i=graph::t[i])
			{
				int v=graph::v[i];
				if(graph::w[i]==1)
				{
					if(d[v]>d[x]+1)
					{
						d[v]=d[x]+1;
						q.push_back(v);
					}
				}
				else
				{
					if(d[v]>d[x])
					{
						d[v]=d[x];
						q.push_front(v);
					}
				}
			}
		}
		int res=min(d[id(0,3)],d[id(0,4)]);
		return res;
	}
}
int check1()
{
	int v1=Sy;
	int v2=Ty;
	if(v1>v2)
		swap(v1,v2);
	for(int i=1;i<=n;i++)
		if(y1[i]>v1&&y1[i]<v2&&x1[i]<Sx&&x2[i]>Sx)
			return 0;
	return 1;
}
int check2()
{
	int v1=Sx;
	int v2=Tx;
	if(v1>v2)
		swap(v1,v2);
	for(int i=1;i<=n;i++)
		if(x1[i]>v1&&x1[i]<v2&&y1[i]<Sy&&y2[i]>Sy)
			return 0;
	return 1;
}
int main()
{
	open("b");
	scanf("%d%d%d%d",&Sx,&Sy,&Tx,&Ty);
	dx[++tx]=Sx;
	dx[++tx]=Tx;
	dy[++ty]=Sy;
	dy[++ty]=Ty;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
//		scanf("%d%d%d%d",&x1[i],&x2[i],&y1[i],&y2[i]);
		x1[i]=rd();
		x2[i]=rd();
		y1[i]=rd();
		y2[i]=rd();
		dx[++tx]=x1[i];
		dx[++tx]=x2[i];
		dy[++ty]=y1[i];
		dy[++ty]=y2[i];
	}
	if(Sx==Tx&&check1())
	{
		printf("1\n");
		return 0;
	}
	else if(Sy==Ty&&check2())
	{
		printf("1\n");
		return 0;
	}
	sort(dx+1,dx+tx+1);
	tx=unique(dx+1,dx+tx+1)-dx-1;
	sort(dy+1,dy+ty+1);
	ty=unique(dy+1,dy+ty+1)-dy-1;
	Sx=lower_bound(dx+1,dx+tx+1,Sx)-dx;
	Sy=lower_bound(dy+1,dy+ty+1,Sy)-dy;
	Tx=lower_bound(dx+1,dx+tx+1,Tx)-dx;
	Ty=lower_bound(dy+1,dy+ty+1,Ty)-dy;
	for(int i=1;i<=n;i++)
	{
		x1[i]=lower_bound(dx+1,dx+tx+1,x1[i])-dx;
		x2[i]=lower_bound(dx+1,dx+tx+1,x2[i])-dx;
		y1[i]=lower_bound(dy+1,dy+ty+1,y1[i])-dy;
		y2[i]=lower_bound(dy+1,dy+ty+1,y2[i])-dy;
	}
	init::gao();
	build::gao();
	int ans=bfs::gao()+1;
	printf("%d\n",ans);
//	printf("nodecnt = %d\n",nodecnt);
	return 0;
}
