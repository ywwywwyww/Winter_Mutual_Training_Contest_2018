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
struct seg
{
	int lc[5000010];
	int rc[5000010];
	ll s1[5000010];
	ll s2[5000010];
	int cnt;
	int rt;
	#define mid ((L+R)>>1)
	void update(int &p,ll v1,ll v2,ll L,ll R)
	{
		if(!p)
		{
			p=++cnt;
			s2[p]=0x9000000000000000ll;
		}
		ll s11=v1*L+v2;
		ll s12=v1*mid+v2;
		ll s13=v1*R+v2;
		ll s21=s1[p]*L+s2[p];
		ll s22=s1[p]*mid+s2[p];
		ll s23=s1[p]*R+s2[p];
		if(s11<=s21&&s13<=s23)
			return;
		if(s11>=s21&&s13>=s23)
		{
			s1[p]=v1;
			s2[p]=v2;
			return;
		}
		if(s12>s22)
		{
			swap(s1[p],v1);
			swap(s2[p],v2);
			swap(s11,s21);
			swap(s12,s22);
			swap(s13,s23);
		}
		if(L==R)
			return;
		if(s11>s21)
			update(lc[p],v1,v2,L,mid);
		else
			update(rc[p],v1,v2,mid+1,R);
	}
	ll query(int p,ll x,ll L,ll R)
	{
		if(!p)
			return 0x9000000000000000ll;
		ll res=s1[p]*x+s2[p];
		if(x<=mid)
			res=max(res,query(lc[p],x,L,mid));
		else
			res=max(res,query(rc[p],x,mid+1,R));
		return res;
	}
}
s1,s2;
int n;
int l[N],r[N];
ll prew[N],w[N],pred[N],d[N];
int b[N];
int main()
{
	open("b");
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		l[i]<<=1;
		r[i]<<=1;
	}
	for(int i=1;i<=n;i++)
	{
		w[i]=r[i]-l[i];
		d[i]=(ll)w[i]*(l[i]+r[i])/2;
		prew[i]=w[i]+prew[i-1];
		pred[i]=d[i]+pred[i-1];
	}
	int last=n;
	int ans=0;
	ll tot=20000ll*n;
	for(int i=n-1;i>=1;i--)
	{
		if(-s1.query(s1.rt,prew[i],1,tot)>=pred[i]&&s2.query(s2.rt,prew[i],1,tot)<=pred[i])
		{
			ans=max(ans,last-i);
			last=i;
		}
		s1.update(s1.rt,-l[i+1],-(pred[i]-l[i+1]*prew[i]),1,tot);
		s2.update(s2.rt,r[i+1],pred[i]-r[i+1]*prew[i],1,tot);
	}
	ans=max(ans,last);
	printf("%d\n",ans);
	return 0;
}
