#pragma GCC diagnostic error "-std=c++11"
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<utility>
#include<cmath>
#include<functional>
#include<vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
void sort(int &a,int &b)
{
	if(a>b)
		swap(a,b);
}
void open(const char *s)
{
#ifndef ONLINE_JUDGE
	char str[100];
	sprintf(str,"%s.in",s);
	freopen(str,"r",stdin);
	sprintf(str,"%s.out",s);
	freopen(str,"w",stdout);
#endif
}
int rd()
{
	int s=0,c,b=0;
	while(((c=getchar())<'0'||c>'9')&&c!='-');
	if(c=='-')
	{
		c=getchar();
		b=1;
	}
	do
	{
		s=s*10+c-'0';
	}
	while((c=getchar())>='0'&&c<='9');
	return b?-s:s;
}
void put(int x)
{
	if(!x)
	{
		putchar('0');
		return;
	}
	static int c[20];
	int t=0;
	while(x)
	{
		c[++t]=x%10;
		x/=10;
	}
	while(t)
		putchar(c[t--]+'0');
}
int upmin(int &a,int b)
{
	if(b<a)
	{
		a=b;
		return 1;
	}
	return 0;
}
int upmax(int &a,int b)
{
	if(b>a)
	{
		a=b;
		return 1;
	}
	return 0;
}

int fp(int a,ll b)
{
	int s=1;
	for(;b;b>>=1,a*=a)
		if(b&1)
			s*=a;
	return s;
}

namespace gao1
{
	const int N=30;
	int n,m;
	vector<int> g[N],g2[N];
	int lx[N*N],ly[N*N];
	int dfn[N],low[N],b[N],st[N],top,c[N],ti,ccnt;
	int f[1<<20],a[N];
	int s[N];
	int d[N][N];
	int inv[N],pw[N];
	void dfs(int x)
	{
		dfn[x]=low[x]=++ti;
		st[++top]=x;
		b[x]=1;
		for(auto v:g[x])
			if(b[v]!=2)
			{
				if(!b[v])
					dfs(v);
				low[x]=min(low[x],low[v]);
			}
		if(low[x]>=dfn[x])
		{
			ccnt++;
			int v;
			do
			{
				v=st[top--];
				b[v]=2;
				c[v]=ccnt;
			}
			while(v!=x);
		}
	}
	void add(int &a,int b)
	{
		a+=b;
	}
	void gao()
	{
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&lx[i],&ly[i]);
			g[lx[i]].push_back(ly[i]);
		}
		for(int i=1;i<=n;i++)
			if(!b[i])
				dfs(i);
		for(int i=1;i<=m;i++)
			if(c[lx[i]]!=c[ly[i]])
			{
				g2[c[lx[i]]].push_back(c[ly[i]]);
				a[c[lx[i]]]|=1<<(c[ly[i]]-1);
			}
		n=ccnt;
		f[0]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				for(int k=0;k<1<<n;k++)
					if(!((k>>(j-1))&1)&&(k&a[j])==a[j])
						add(f[k|(1<<(j-1))],f[k]);
			s[i]=f[(1<<n)-1];
		}
		for(int i=0;i<=n;i++)
		{
			d[i][0]=1;
			for(int j=1;j<=i;j++)
				d[i][j]=d[i-1][j-1]+d[i-1][j];
		}
		for(int i=n;i>=1;i--)
		{
			for(int j=i-1;j>=1;j--)
				s[i]+=((i-j)&1?-1:1)*d[i][j]*s[j];
		}
		for(int i=1;i<=n;i++)
		{
			int x=i;
			while(!(x&1))
			{
				pw[i]++;
				x>>=1;
			}
			inv[i]=fp(x,(1ll<<31)-1);
		}
	}
	int query(ll x)
	{
		int res=0;
		int prod=1;
		int num=0;
		for(int i=1;i<=n&&i<=x;i++)
		{
			ll y=x-i+1;
			while(num<=20&&!(y&1))
			{
				y>>=1;
				num++;
			}
			num-=pw[i];
			prod*=inv[i];
			prod*=y;
			res+=(prod<<num)*s[i];
		}
		return res;
	}
}

namespace gao2
{
	const int M=100010;
	const int m=100000;
	ll n;
	int pri[M],b[M],cnt;
	int f1[M],f2[M],s1[M],s2[M];
	void init()
	{
		for(int i=2;i<=m;i++)
		{
			if(!b[i])
				pri[++cnt]=i;
			for(int j=1;j<=cnt&&i*pri[j]<=m;j++)
			{
				b[i*pri[j]]=1;
				if(i%pri[j]==0)
					break;
			}
		}
	}
	void gao()
	{
		init();
		int mx=n/(m+1);
		for(int i=2;i<=m;i++)
			f1[i]=i-1;
		for(int i=1;i<=mx;i++)
			f2[i]=n/i-1;
		for(int i=1;i<=cnt;i++)
		{
			int x=pri[i];
			int y=f1[x-1];
			int mx1=min(n/x/(m+1),n/x/x);
			int mx2=min((ll)mx,n/x/x);
			ll p2=(ll)pri[i]*pri[i];
			ll o=n/x;
			for(int j=1;j<=mx1;j++)
				f2[j]-=f2[j*x]-y;
			for(int j=mx1+1;j<=mx2;j++)
				f2[j]-=f1[o/j]-y;
			for(int j=m;j>=p2;j--)
				f1[j]-=f1[j/x]-y;
		}
		for(int i=2;i<=m;i++)
		{
			f1[i]*=63;
			s1[i]=f1[i];
		}
		for(int i=1;i<=mx;i++)
		{
			f2[i]*=63;
			s2[i]=f2[i];
		}
		for(int i=cnt;i>=1;i--)
		{
			int x=pri[i];
			int mx1=min((ll)mx,n/x/x);
			for(int j=1;j<=mx1;j++)
			{
				s2[j]-=63;
				ll x2=n/j/x;
				for(int k=1;x2;x2/=x,k++)
					s2[j]+=((x2<=m?s1[x2]-f1[min((int)x2,x)]:s2[n/x2]-f1[x])+1)*(81*k*k-27*k+9);
			}
			ll mn=(ll)pri[i]*pri[i];
			for(int j=m;j>=mn;j--)
			{
				s1[j]-=63;
				int x2=j/x;
				for(int k=1;x2;x2/=x,k++)
					s1[j]+=(s1[x2]-f1[min(x2,x)]+1)*(81*k*k-27*k+9);
			}
		}
	}
	int query(ll x)
	{
		if(x<=0)
			return 0;
		return (x<=m?s1[x]:s2[n/x])+1;
	}
}

int main()
{
	scanf("%d%lld",&gao1::n,&gao2::n);
	gao1::gao();
	gao2::gao();
	int ans=0;
	ll n=gao2::n;
	for(ll i=1,j;i<=n;i=j+1)
	{
		j=n/(n/i);
		ans+=(gao2::query(j)-gao2::query(i-1))*gao1::query(n/i);
	}
	printf("%u\n",ans);
	return 0;
}
