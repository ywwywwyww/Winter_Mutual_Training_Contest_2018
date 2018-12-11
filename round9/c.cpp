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
const ll p=998244353;
const ll p1=1000000007;
const ll p2=1000000009;
const int N=200010;
int n;
struct sa
{
	char s[N];
	int b[N];
	int x[N];
	int y[N];
	int sa[N];
	int rk[N];
	int ht[N];
	int f[20][N];
	int l[N];
	int getmin(int x,int y)
	{
		int k=l[y-x+1];
	    return min(f[k][x],f[k][y-(1<<k)+1]);
	}
	void init()
	{
	//  freopen("xsy2361.in","r",stdin);
	    int n,i,j,k,p,sz;
	    scanf("%s",s+1);
	    n=strlen(s+1);
	    sz=26;
	    for(i=1;i<=sz;i++)
	        b[i]=0;
	    for(i=1;i<=n;i++)
	        b[x[i]=s[i]-'a'+1]++;
	    for(i=2;i<=sz;i++)
	        b[i]+=b[i-1];
	    for(i=n;i>=1;i--)
	        sa[b[x[i]]--]=i;
	    for(k=1;k<=n;k<<=1)
	    {
	        p=0;
	        for(i=n-k+1;i<=n;i++)
	            y[++p]=i;
	        for(i=1;i<=n;i++)
	            if(sa[i]>k)
	                y[++p]=sa[i]-k;
	        for(i=1;i<=sz;i++)
	            b[i]=0;
	        for(i=1;i<=n;i++)
	            b[x[y[i]]]++;
	        for(i=2;i<=sz;i++)
	            b[i]+=b[i-1];
	        for(i=n;i>=1;i--)
	            sa[b[x[y[i]]]--]=y[i];
	        swap(x,y);
	        p=1;
	        for(i=1;i<=n;i++)
	            if(i==1||y[sa[i]]==y[sa[i-1]]&&(sa[i]+k>n&&sa[i-1]+k>n||sa[i]+k<=n&&sa[i-1]+k<=n&&y[sa[i]+k]==y[sa[i-1]+k]))
	                x[sa[i]]=p;
	            else
	                x[sa[i]]=++p;
	        if(p>=n)
	            break;
	        sz=p;
	    }
	    for(i=1;i<=n;i++)
	        rk[sa[i]]=i;
	    p=0;
	    for(i=1;i<=n;i++)
	        if(rk[i]==1)
	            ht[rk[i]]=0;
	        else
	        {
	            if(p)
	                p--;
	            while(i+p<=n&&sa[rk[i]-1]+p<=n&&s[i+p]==s[sa[rk[i]-1]+p])
	                p++;
	            ht[rk[i]]=p;
	        }
	    for(i=1;i<=n;i++)
	        f[0][i]=ht[i];
	    for(i=1;(1<<i)<=n;i++)
	        for(j=1;j<=n;j++)
	            if(j+(1<<i)-1<=n)
	                f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	    l[1]=0;
	    for(int i=2;i<=n;i++)
	    	l[i]=l[i>>1]+1;
	}
	int query(int x,int y)
	{
		if(rk[x]>rk[y])
			swap(x,y);
		return getmin(rk[x]+1,rk[y]);
	}
}
lcp,lcs;
char s[N];
namespace hash
{
//	ll w1[N],w2[N];
//	ll h1[N],h2[N];
//	ll gethash1(int x,int y)
//	{
//		return (h1[y]-h1[x-1]*w1[y-x+1]%p1+p1)%p1;
//	}
//	ll gethash2(int x,int y)
//	{
//		return (h2[y]-h2[x-1]*w2[y-x+1]%p2+p2)%p2;
//	}
//	int equal(int l1,int r1,int l2,int r2)
//	{
//		return gethash1(l1,r1)==gethash1(l2,r2)&&gethash2(l1,r1)==gethash2(l2,r2);
//	}
//	void init()
//	{
//		w1[0]=w2[0]=1;
//		for(int i=1;i<=n;i++)
//		{
//			w1[i]=w1[i-1]*127%p1;
//			w2[i]=w2[i-1]*127%p2;
//			h1[i]=(h1[i-1]*127+s[i])%p1;
//			h2[i]=(h2[i-1]*127+s[i])%p2;
//		}
//	}
//	int getlcp(int x,int y)
//	{
//		int l=0,r=min(n-x+1,n-y+1);
//		while(l<r)
//		{
//			int mid=(l+r+1)>>1;
//			if(equal(x,x+mid-1,y,y+mid-1))
//				l=mid;
//			else
//				r=mid-1;
//		}
//		return l;
//	}
//	int getlcs(int x,int y)
//	{
//		int l=0,r=min(x,y);
//		while(l<r)
//		{
//			int mid=(l+r+1)>>1;
//			if(equal(x-mid+1,x,y-mid+1,y))
//				l=mid;
//			else
//				r=mid-1;
//		}
//		return l;
//	}
	void init()
	{
		for(int i=1;i<=n;i++)
		{
			lcp.s[i]=s[i];
			lcs.s[i]=s[n-i+1];
		}
		lcp.init();
		lcs.init();
	}
	int getlcp(int x,int y)
	{
		return lcp.query(x,y);
	}
	int getlcs(int x,int y)
	{
		return lcs.query(n-x+1,n-y+1);
	}
}
const int M=10000000;
ll f[N];
int pre[N];
int ban[M];
ll period[M];
ll h[M];
vector<pii> g[N];
int main()
{
	open("c");
	scanf("%s",s+1);
	n=strlen(s+1);
	hash::init();
	for(int i=1;i<=n;i++)
		pre[i]=pre[i-1]+n/i-1;
	int tot=0;
	for(int i=1;i<=n/2;i++)
	{
		int l=-1,r=-1;
		for(int j=i;j+i<=n;j+=i)
		{
			if(j<=r)
				continue;
			int l1=hash::getlcs(j,j+i);
			int l2=hash::getlcp(j,j+i);
			if(l1+l2<i+1)
				continue;
			l=j-l1+1;
			r=j+l2-1;
			if(ban[pre[i-1]+j/i])
				continue;
			for(int k=2*i;l+2*k-1<=r+i;k+=i)
				ban[pre[k-1]+(l-1)/k+1]=1;
			int last=tot;
			for(int k=l;k<=r-i+1;k++)
			{
				if(k<=l+i-1)
					tot++;
				g[k+2*i-1].push_back(pii(i,last+(k-l)%i));
			}
		}
	}
	f[0]=1;
	ll sum=1;
	for(int i=1;i<=n;i++)
	{
		f[i]=sum;
		for(auto v:g[i])
		{
			int x=v.first,y=v.second;
			period[y]=(period[y]+f[i-2*x])%p;
			h[y]=-(h[y]+f[i-2*x])%p;
			f[i]=(f[i]+h[y])%p;
			f[i]=(f[i]-period[y])%p;
		}
		sum=(sum+f[i])%p;
	}
	ll ans=f[n];
	ans=(ans+p)%p;
	printf("%lld\n",ans);
	return 0;
}
