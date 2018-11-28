#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
//#include<cmath>
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
int n,k;
ll p;
int sz;
struct mat
{
	ll a[82][82];
	mat()
	{
		memset(a,0,sizeof a);
	}
	ll *operator [](int x)
	{
		return a[x];
	}
};
mat operator *(mat a,mat b)
{
	mat c;
	for(int i=1;i<=sz;i++)
		for(int j=1;j<=sz;j++)
		{
			__int128 s=0;
			for(int l=1;l<=sz;l++)
				s+=(__int128)a[i][l]*b[l][j];
			c[i][j]=s%p;
		}
	return c;
}
mat fp(mat a,ll b)
{
	mat s;
	for(int i=1;i<=sz;i++)
		s[i][i]=1;
	for(;b;b>>=1,a=a*a)
		if(b&1)
			s=s*a;
	return s;
}
ll s[30][2][2][2][10][10];
int b[100];
int id(int x,int y)
{
	return x*(k+1)+y+1;
}
int x1,y1,z1;
int check(int x,int y,int z)
{
	return x>=x1&&x<=k&&y>=y1&&y<=k&&z>=z1&&z<=k;
}
void gao(int x,int _x1,int _y1,int _z1)
{
	x1=_x1;
	y1=_y1;
	z1=_z1;
	memset(b,0,sizeof b);
	int cnt=0;
	for(int i=0;i<=k;i++)
		for(int j=0;j<=k;j++)
			if(check(i,j,-x-i-j))
				b[id(i,j)]=++cnt;
//	printf("%d\n",cnt);
	mat a;
	for(int i=0;i<=k;i++)
		for(int j=0;j<=k;j++)
			if(b[id(i,j)])
			{
				if(check(i+1,j,-x-i-j-1))
					a[b[id(i,j)]][b[id(i+1,j)]]++;
				if(check(i-1,j+1,-x-i-j))
					a[b[id(i,j)]][b[id(i-1,j+1)]]++;
				if(check(i,j-1,-x-i-j+1))
					a[b[id(i,j)]][b[id(i,j-1)]]++;
			}
	sz=cnt;
	a=fp(a,n);
	for(int i=0;i<=k;i++)
		for(int j=0;j<=k;j++)
			if(check(i,j,-x-i-j))
			{
				ll temp=0;
				for(int l=1;l<=sz;l++)
					temp=(temp+a[b[id(i,j)]][l])%p;
				s[x+3*k][x1][y1][z1][i][j]=temp;
			}
}
ll calc(int x,int x1,int y,int y1,int z,int z1)
{
	return s[x+y+z+3*k][x1][y1][z1][-x][-y];
}
int main()
{
	open("c");
	scanf("%d%d%lld",&n,&k,&p);
	sz=(k+1)*(k+1);
	for(int i=-3*k;i<=0;i++)
		for(int i1=0;i1<=1;i1++)
			for(int j1=0;j1<=1;j1++)
				for(int l1=0;l1<=1;l1++)
					gao(i,i1,j1,l1);
	ll ans=0;
	for(int i=-k;i<=0;i++)
		for(int j=-k;j<=0;j++)
			for(int l=-k;l<=0;l++)
			{
				ll temp=0;
				temp+=calc(i,0,j,0,l,0);
				temp-=calc(i,0,j,0,l,1);
				temp-=calc(i,0,j,1,l,0);
				temp+=calc(i,0,j,1,l,1);
				temp-=calc(i,1,j,0,l,0);
				temp+=calc(i,1,j,0,l,1);
				temp+=calc(i,1,j,1,l,0);
				temp-=calc(i,1,j,1,l,1);
				ans=(ans+temp)%p;
			}
	ans=(ans%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
