#include <bits/stdc++.h>
#define MAXN 200010
#define LL long long
using namespace std;

int read(){
	char c;
	while((c=getchar())<'0' || c>'9');
	int res=c-'0';
	while((c=getchar())>='0' && c<='9') res=res*10+c-'0';
	return res;
}

struct V{
	LL a,b;

	V(LL _a=0,LL _b=0):a(_a),b(_b){}

	friend bool operator<(V x,V y){
		if(x.b>=0 && y.b>=0)
			return x.b-x.a<y.b-y.a;
		if(x.b<0 && y.b<0)
			return x.a<y.a;
		return x.b<0;
	}

	friend V operator+(V x,V y){
		return V(max(x.a,x.b+y.a),x.b+y.b);
	}
};

namespace Splay{
	struct node{
		V v,max,s;
		int ch[2],p,cnt;
	}a[MAXN];

	void pushup(int x){
		a[x].cnt=a[a[x].ch[0]].cnt+a[a[x].ch[1]].cnt+1;
		a[x].s=a[a[x].ch[0]].s+a[x].v+a[a[x].ch[1]].s;
		a[x].max=a[x].ch[1]?a[a[x].ch[1]].max:a[x].v;
	}

	void rotate(int x){
		int p=a[x].p,d=(a[p].ch[0]==x);
		if(a[p].p) a[a[p].p].ch[a[a[p].p].ch[1]==p]=x;
		a[x].p=a[p].p;
		a[p].ch[d^1]=a[x].ch[d];
		if(a[x].ch[d]) a[a[x].ch[d]].p=p;
		a[x].ch[d]=p;
		a[p].p=x;
		pushup(p);
		pushup(x);
	}

	void splay(int x){
		while(a[x].p){
			int p=a[x].p;
			if(!a[p].p) rotate(x);
			else{
				int q=a[p].p;
				if((a[p].ch[1]==x)==(a[q].ch[1]==p)) rotate(p),rotate(x);
				else rotate(x),rotate(x);
			}
		}
	}

	int insert(int x,int y){
		if(!x) return y;
		while(1){
			if(a[y].v<a[x].v){
				if(!a[x].ch[0]){
					a[x].ch[0]=y;
					a[y].p=x;
					break;
				}
				x=a[x].ch[0];
			}else{
				if(!a[x].ch[1]){
					a[x].ch[1]=y;
					a[y].p=x;
					break;
				}
				x=a[x].ch[1];
			}
		}
		splay(y);
		return y;
	}

	int remove_max(int x){
		while(a[x].ch[1]) x=a[x].ch[1];
		splay(x);
		a[a[x].ch[0]].p=0;
		return a[x].ch[0];
	}

	int merge(int x,int y){
		if(!x) return y;
		if(a[x].cnt>a[y].cnt) return merge(y,x);
		int temp=merge(a[x].ch[0],y);
		int rc=a[x].ch[1];
		a[x].ch[0]=a[x].ch[1]=a[x].p=0;
		pushup(x);
		temp=insert(temp,x);
		return merge(rc,temp);
	}
}

int n;
int v[MAXN];
pair<LL,LL> a[MAXN];
vector<int> ch[MAXN];
int root[MAXN];
LL ans[MAXN];

void dfs(int x){
	root[x]=0;
	for(int i:ch[x]){
		dfs(i);
		root[x]=Splay::merge(root[x],root[i]);
	}
	V cv(a[x].first,a[x].second);
	while(root[x] && !(Splay::a[root[x]].max<cv)){
		cv=Splay::a[root[x]].max+cv;
		root[x]=Splay::remove_max(root[x]);
	}
	Splay::a[x].v=cv;
	Splay::pushup(x);
	root[x]=Splay::insert(root[x],x);
	ans[x]=Splay::a[root[x]].s.a;
}

int main(){
	freopen("a.in","r",stdin);
	freopen("a3.out","w",stdout);
	read();
	n=read();
	for(int i=2;i<=n;i++) ch[read()].push_back(i);
	for(int i=1;i<=n;i++) v[i]=read();
	for(int i=1;i<=n;i++){
		a[i].first=a[i].second=v[i];
		for(int j:ch[i]) a[i].second-=v[j];
	}
	dfs(1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}

