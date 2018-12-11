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
typedef __int128 lll;
const int N=100010;
ll ax[N],ay[N];
lll cross(pll a,pll b)
{
	return (lll)a.first*b.second-(lll)a.second*b.first;
}
pll operator -(pll a,pll b)
{
	return pll(a.first-b.first,a.second-b.second);
}
lll calc(pll a,ll x)
{
	return (lll)a.first*x+a.second;
}
namespace seg
{
	#define mid ((L+R)>>1)
	#define lc (p<<1)
	#define rc ((p<<1)|1)
	vector<pll> s[1000000];
	int pos[1000000];
	void build(int p,int L,int R)
	{
		s[p].clear();
		pos[p]=0;
		if(L==R)
		{
			s[p].push_back(pll(ax[L],ay[L]));
			return;
		}
		build(lc,L,mid);
		build(rc,mid+1,R);
		static vector<pll> b;
		b.clear();
		b.resize(s[lc].size()+s[rc].size());
		std::merge(s[lc].begin(),s[lc].end(),s[rc].begin(),s[rc].end(),b.begin(),std::greater<pll>());
		for(auto &v:b)
		{
			while(s[p].size()>=2&&cross(v-s[p].back(),s[p].back()-s[p][s[p].size()-2])<=0)
				s[p].pop_back();
			s[p].push_back(v);
		}
	}
	ll query(int p,int l,int r,ll v,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			while(pos[p]<(int)s[p].size()-1&&calc(s[p][pos[p]+1],v)<=calc(s[p][pos[p]],v))
				pos[p]++;
			return min((lll)1e18,(lll)calc(s[p][pos[p]],v));
		}
		ll res=1e18;
		if(l<=mid)
			res=min(res,query(lc,l,r,v,L,mid));
		if(r>mid)
			res=min(res,query(rc,l,r,v,mid+1,R));
		return res;
	}
	#undef mid
}
ll f[N];
ll e[N];
ll w[N];
ll t[N];
ll c[N];
ll maxt[N];
ll minf[N];
int n;
struct info
{
	ll l,r,v,id;
};
info a[N];
int cmp(info a,info b)
{
	return a.v<b.v;
}
int cnt;
void solve(int l,int r)
{
	if(l==r)
	{
		f[l]=min((lll)f[l],f[l-1]+(lll)t[l]*e[l]);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	maxt[mid]=t[mid];
	for(int i=mid-1;i>=l;i--)
		maxt[i]=max(t[i],maxt[i+1]);
	maxt[mid+1]=t[mid+1];
	for(int i=mid+2;i<=r;i++)
		maxt[i]=max(t[i],maxt[i-1]);
	for(int i=mid+1;i<=r;i++)
		minf[i]=1e18;
	for(int i=mid;i>=l;i--)
		minf[i]=min(f[i-1],minf[i+1]);
	cnt=0;
	for(int i=mid+1,j=mid+1;i<=r;i++)
	{
		while(j>l&&maxt[j-1]<=maxt[i])
			j--;
		f[i]=min((lll)f[i],minf[max(c[i],(ll)j)]+(lll)maxt[i]*e[i]);
		int li=max((ll)l,c[i]);
		int ri=j-1;
		if(li<=ri)
		{
			cnt++;
			a[cnt].v=e[i];
			a[cnt].l=li-l+1;
			a[cnt].r=ri-l+1;
			a[cnt].id=i;
		}
	}
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=mid-l+1;i++)
	{
		ax[i]=maxt[i+l-1];
		ay[i]=f[i+l-2];
	}
	seg::build(1,1,mid-l+1);
	
	for(int i=1;i<=cnt;i++)
		f[a[i].id]=min(f[a[i].id],seg::query(1,a[i].l,a[i].r,a[i].v,1,mid-l+1));
	
	solve(mid+1,r);
}
int main()
{
	open("a");
	n=rd();
	for(int i=1;i<=n;i++)
	{
		c[i]=rd();
		c[i]++;
		t[i]=rd();
		w[i]=rd();
	}
	for(int i=n;i>=1;i--)
		e[i]=e[i+1]+w[i+1];
	for(int i=1;i<=n;i++)
		f[i]=1e18;
	solve(1,n);
	printf("%lld\n",f[n]);
	return 0;
}
