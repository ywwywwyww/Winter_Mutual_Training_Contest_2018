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
const ll p=1000000007;
const int N=210;
const int M=100000;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
int n,m,A;
int a[N];
int fa[N],fail[N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	fa[find(x)]=find(y);
}
int gao(int len)
{
	for(int i=1;i<=len;i++)
		fa[i]=i;
	for(int i=1;i<len;i++)
		if(a[i])
		{
			for(int j=1;j<=i;j++)
				merge(j,len-i+j);
		}
	for(int i=1;i<len;i++)
		if(!a[i])
		{
			int flag=1;
			for(int j=1;j<=i;j++)
				if(find(j)!=find(len-i+j))
				{
					flag=0;
					break;
				}
			if(flag)
				return -1;
		}
	fail[1]=0;
	for(int i=2;i<=len;i++)
	{
		for(fail[i]=fail[i-1];fail[i]&&find(fail[i]+1)!=find(i);fail[i]=fail[fail[i]]);
		if(find(fail[i]+1)==find(i))
			fail[i]++;
	}
	return fail[len];
}
int c[M][N];
int cnt;
void dfs(int x)
{
	if(x==m)
	{
		a[m]=1;
		cnt++;
		for(int i=1;i<=m;i++)
			c[cnt][i]=a[i];
//		for(int i=1;i<=m;i++)
//			putchar(a[i]+'0');
//		putchar('\n');
		return;
	}
	a[x]=1;
	for(int i=x+1;i<=m;i++)
		if(2*x<i)
		{
			dfs(i);
		}
		else
		{
			if(gao(i)==x)
				dfs(i);
		}
	a[x]=0;
}
ll s[M];
ll pw[N];
void calc(int x)
{
	for(int i=1;i<=m;i++)
		fa[i]=i;
	for(int i=1;i<m;i++)
		if(c[x][i])
		{
			for(int j=1;j<=i;j++)
				merge(j,m-i+j);
		}
	int cnt=0;
	for(int i=1;i<=m;i++)
		if(find(i)==i)
			cnt++;
	s[x]=fp(A,cnt);
}
ll f[N],g[N],h[N];
ll ans;
void dp(int x)
{
	for(int i=1;i<=m;i++)
		a[i]=c[x][i];
	for(int i=1;i<=n;i++)
		f[i]=g[i]=h[i]=0;
	for(int i=1;i<=n;i++)
		if(i<m)
		{
			if(a[m-i])
				h[i]=1;
		}
		else
			h[i]=pw[i-m];
	
	g[0]=1;		
	for(int i=1;i<=n;i++)
	{
		g[i]=h[i];
		for(int j=1;j<i;j++)
			g[i]=(g[i]-h[j]*g[i-j])%p;
	}
	
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		f[i]=pw[i];
		for(int j=1;j<=i;j++)
			f[i]=(f[i]-h[j]*f[i-j])%p;
	}
	
	ll res=0;
	for(int i=1;i<=n-m+1;i++)
		res=(res+pw[i-1]*f[n-i+1-m])%p;
	
	ans=(ans+res*s[x])%p;
}
int main()
{
	open("a");
	scanf("%d%d%d",&n,&m,&A);
	for(int i=1;i<=m;i++)
		dfs(i);
//	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		calc(i);
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<i;j++)
		{
			int flag=1;
			for(int k=1;k<=m;k++)
				if(c[i][k]&&!c[j][k])
				{
					flag=0;
					break;
				}
			if(flag)
				s[i]=(s[i]-s[j])%p;
		}
	pw[0]=1;
	for(int i=1;i<=n;i++)
		pw[i]=pw[i-1]*A%p;
	for(int i=1;i<=cnt;i++)
		dp(i);
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
