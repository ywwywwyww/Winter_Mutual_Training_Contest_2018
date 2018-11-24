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
namespace LIB{
    const int N=30;
    int dim[N],dimcnt;
    template<class T>void dfs(int dep,T g,int x,int y,int z,int n){
        if(dep>dimcnt)return g[x][y]=z,void();
        int d=n/dim[dep];
        for(int i=0;i<n;i+=d){
            for(int j=0;j<n;j+=d){
                dfs(dep+1,g,x+i,y+j,z+(i+j)%n,d);
            }
        }
    }
    template<class T1,class T2>inline int put_reaction(int t,T1 a,T2 g){
        dimcnt=t;
        int n=1;
        for(int i=1;i<=t;i++){
            n*=dim[i]=a[i];
        }
        dfs(1,g,1,1,1,n);
        return n;
    }
}
char str[30000000];
int cnt;
int rd()
{
	int s=0,c;
	while((c=str[cnt++])<'0'||c>'9');
	do
	{
		s=s*10+c-'0';
	}
	while((c=str[cnt++])>='0'&&c<='9');
	return s;
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
int n,t,m,q;
int c[3010];
int top;
int st[3010],ed[3010];
int a[1000];
int e[3010];
short b[1000010];
int w[3010];
int high[3010];
short g[3010][3010];
short g2[3010][3010];
short g3[3010][3010];
int del(int x,int y)
{
	int s=0;
	for(int i=1;i<=top;i++)
	{
		int x1=x/w[i+1]%c[i];
		int y1=y/w[i+1]%c[i];
		int z1=(x1-y1+c[i])%c[i];
		s+=z1*w[i+1];
	}
	return s;
}
int mul(int x,int y)
{
	int s=0;
	x%=n;
	for(int i=1;i<=top;i++)
	{
		int y1=y/w[i+1]%c[i];
		int z1=x*y1%c[i];
		s+=z1*w[i+1];
	}
	return s;
}
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
short gx[3010][3010];
short gy[3010][3010];
short gd[3010][3010];
bool gb[3010][3010];
void exgcd(int a,int b)
{
    if(!b)
    {
    	gx[a][b]=1;
    	gy[a][b]=0;
    	gd[a][b]=a;
        return;
    }
    if(!gb[b][a%b])
    	exgcd(b,a%b);
    gb[b][a%b]=1;
    int d=gd[b][a%b];
	int y=gx[b][a%b];
	int x=gy[b][a%b];
    y-=a/b*x;
    gx[a][b]=x;
    gy[a][b]=y;
    gd[a][b]=d;
}
struct zjtwfak
{
	int a[13];
	void clear()
	{
		memset(a,0,sizeof a);
	}
	zjtwfak()
	{
		clear();
	}
	int insert(int x)
	{
		if(!x)
			return 0;
		int i=high[x];
		int v=x/w[i+1];
		int y=a[i]/w[i+1];
		int a1,d;
		if(y)
		{
			d=gd[y][c[i]];
			a1=gx[y][c[i]];
			if(v%d==0)
				return insert(g2[x][g3[a[i]][a1*v/d%n]]);
		}
		d=gd[v][c[i]];
		a1=gx[v][c[i]];
		if(y)
			insert(g2[a[i]][g3[x][a1*y/d%n]]);
		a[i]=x;
		insert(g3[x][c[i]/d]);
		return 1;
	}
	int calc()
	{
		int s=1;
		for(int i=1;i<=top;i++)
			if(a[i])
				s*=c[i]/gcd(c[i],a[i]/w[i+1]);
		return s;
	}
};
int gao(int x)
{
	int s=0;
	for(int i=1;i<=t;i++)
	{
		int v=x/w[ed[i]+1]%a[i];
		for(int j=st[i];j<=ed[i];j++)
			s+=v%c[j]*w[j+1];
	}
	return s;
}
zjtwfak ans;
vector<pii> f[1000010];
int l[1000010];
int r[1000010];
short s[1000010];
void del(int x)
{
	l[r[x]]=l[x];
	r[l[x]]=r[x];
}
int main()
{
	open("c");
	fread(str,1,30000000,stdin);
	cnt=0;
	t=rd();
	m=rd();
	q=rd();
//	scanf("%d%d%d",&t,&m,&q);
	n=1;
	for(int i=1;i<=t;i++)
	{
//		scanf("%d",&a[i]);
		a[i]=rd();
		n*=a[i];
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			exgcd(i,j);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(gx[i][j]<0)
				gx[i][j]+=j/gd[i][j];
	top=0;
	for(int i=1;i<=t;i++)
	{
		st[i]=top+1;
		int x=a[i];
		for(int j=2;j*j<=x;j++)
			if(x%j==0)
			{
				int s=1;
				while(x%j==0)
				{
					x/=j;
					s*=j;
				}
				c[++top]=s;
			}
		if(x!=1)
			c[++top]=x;
		ed[i]=top;
	}
    LIB::put_reaction(top,c,g);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		g2[g[i][j]-1][i-1]=j-1;
	for(int i=0;i<n;i++)
	{
		g3[i][0]=0;
		for(int j=1;j<n;j++)
			g3[i][j]=g[g3[i][j-1]+1][i+1]-1;
	}
	w[top+1]=1;
	for(int i=top;i>=1;i--)
		w[i]=w[i+1]*c[i];
	for(int i=0;i<n;i++)
		e[i]=gao(i);
	for(int i=1;i<=m;i++)
		b[i]=e[rd()-1];
	for(int i=0;i<n;i++)
		for(int j=1;j<=top;j++)
			if(i/w[j+1])
			{
				high[i]=j;
				break;
			}
	for(int i=1;i<=q;i++)
	{
		int l=rd();
		int r=rd();
		f[l].push_back(pii(r,i));
	}
	for(int i=1;i<=m;i++)
	{
		l[i]=i-1;
		r[i]=i+1;
	}
	r[m+1]=m;
	l[0]=1;
	for(int i=m;i>=1;i--)
	{
		int sz=f[i].size();
		if(!sz)
			continue;
		sort(f[i].begin(),f[i].end());
		int k=0;
		ans.clear();
		for(int j=i;k<sz&&j<=m;j=r[j])
		{
			if(!ans.insert(b[j]))
				del(j);
			while(k<sz&&f[i][k].first>=j&&f[i][k].first<r[j])
			{
				s[f[i][k].second]=ans.calc();
				k++;
			}
		}
	}
	for(int i=1;i<=q;i++)
	{
//		printf("%d\n",s[i]);
		put(s[i]);
		putchar('\n');
	}
	return 0;
}
