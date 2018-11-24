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
const int K=160;
const ll p=998244353;
ll n;
int k;
struct matrix
{
	int a[K][K];
	matrix()
	{
		memset(a,0,sizeof a);
	}
	int *operator [](int x)
	{
		return a[x];
	}
};
matrix operator *(matrix a,matrix b)
{
	matrix c;
	for(int i=0;i<=k;i++)
		for(int j=0;j<=k;j++)
		{
			__int128 d=0;
			for(int l=0;l<=k;l++)
				d+=(__int128)a[i][l]*b[l][j];
			c[i][j]=d%p;
		}
	return c;
}
matrix fp(matrix a,ll b)
{
	matrix s;
	for(int i=0;i<=k;i++)
		s[i][i]=1;
	for(;b;b>>=1,a=a*a)
		if(b&1)
			s=s*a;
	return s;
}

matrix pw[70],shift;
matrix solve(ll x,int y)
{
	if(x==0)
	{
		matrix s;
		for(int i=0;i<=k;i++)
			s[i][i]=1;
		return s;
	}
	return solve(x/k,y+1)*fp(pw[y],x%k);
}
int main()
{
	open("c");
	scanf("%lld%d",&n,&k);
	for(int i=1;i<=k;i++)
		shift[i][i%k+1]=1;
	shift[0][0]=1;
	pw[0][0][0]=2;
	pw[0][0][1]=1;
	pw[0][1][0]=-1;
	for(int i=2;i<=k;i++)
		pw[0][i][i]=1;
	pw[0]=pw[0]*shift;
	__int128 s=1;
	for(int i=1;s<=n;s*=k,i++)
		pw[i]=fp(pw[i-1],k)*shift;
	matrix a=solve(n,0);
	ll ans=a[0][0];
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
