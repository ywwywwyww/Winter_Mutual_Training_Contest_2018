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
ll n;
int m;
int gao(ll *c,ll v,ll _n,ll _m,ll p1,int p2)
{
	if(c[_m]+v<_n-1)
		return 0;
	while(1)
	{
		if(p1>=_n)
			return 1;
		if(c[p2]<p1)
		{
			int j=p2;
			while(j<_m&&
		}
		else
		{
		}
	return 0;
}
int check(ll *c,ll v)
{
	ll _n=n;
	int _m=m;
	int j=1;
	int now=1;
	while(j<_m&&c[j+1]<=v+1)
		j++;
	if(j>=3)
	{
		ll k=c[2]-v;
		if(k<0)
		{
			k+=_n;
			_n=k;
			while(_m&&c[_m]>_n)
				_m--;
		}
		now=j;
	}
	else if(j==2)
	{
		//left
		ll k=c[2]-v;
		ll __n=_n;
		int __m=_m;
		if(k<0)
		{
			k+=__n;
			__n=k;
			while(__m&&c[__m]>__n)
				__m--;
		}
		if(gao(c,v,__n,__m,c[1],2))
			return 1;
		//right
		now=2;
	}
	else
		now=1;
	return gao(c,v,_n,_m,c[now],now);
}
ll a[N],b[N];
int check(ll v)
{
	return check(a,v)||check(b,v);
}
int main()
{
	open("c");
	scanf("%lld%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+m+1);
	for(int i=m;i>=1;i--)
		a[i]-=a[1];
	for(int i=1;i<=m;i++)
		b[i]=a[i];
	reverse(b+2,b+m+1);
	for(int i=1;i<=m;i++)
	{
		b[i]=-b[i];
		if(b[i]<0)
			b[i]+=n;
	}
//	ll l=0,r=n;
	ll l=3,r=4;
	while(l<r)
	{
		ll mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%lld\n",l);
	return 0;
}
