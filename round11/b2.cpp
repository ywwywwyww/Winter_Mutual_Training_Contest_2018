#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<set>
#include<map>
using namespace std;
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
const int N=310;
set<ull> c;
int a[N][N];
char s[N];
int n;
map<ll,map<ll,int> > c1;
void check(int x,int y)
{
	for(;x>=1&&y<=n&&s[x]==s[y];x--,y++)
		a[x][y]=1;
}
namespace hs
{
	const ll p[2]={1000000007,1000000009};
	ll w[2][N];
	ll h1[2][N],h2[2][N];
	ll query1(int x,int y)
	{
		ll ans=0;
		for(int i=1;i>=0;i--)
		{
			ans+=(h1[i][y]-h1[i][x-1]*w[i][y-x+1]%p[i]+p[i])%p[i];
			if(i)
				ans*=p[i];
		}
		return ans;
	}
	ll query2(int x,int y)
	{
		ll ans=0;
		for(int i=1;i>=0;i--)
		{
			ans+=(h2[i][x]-h2[i][y+1]*w[i][y-x+1]%p[i]+p[i])%p[i];
			if(i)
				ans*=p[i];
		}
		return ans;
	}
	int is_palindrome(int x,int y)
	{
		return query1(x,y)==query2(x,y);
	}
	void init()
	{
		for(int j=0;j<=1;j++)
		{
			w[j][0]=1;
			for(int i=1;i<=n;i++)
			{
				w[j][i]=(w[j][i-1]*127)%p[j];
				h1[j][i]=(h1[j][i-1]*127+s[i])%p[j];
			}
			for(int i=n;i>=1;i--)
				h2[j][i]=(h2[j][i+1]*127+s[i])%p[j];
		}
	}
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b2.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	hs::init();
	for(int i=1;i<=n;i++)
	{
		check(i,i);
		if(i<n)
			check(i,i+1);
	}
	for(int i=1;i<=n;i++)
	{
		ull hs=0;
		for(int j=i;j<=n;j++)
		{
			hs=hs*127+s[j];
			int cnt=0;
			for(int k=i;k<j;k++)
				if(a[i][k]&&a[k+1][j])
				{
					cnt++;
					c1[hs::query1(i,k)][hs::query1(k+1,j)]=1;
				}
			if(cnt)
				c.insert(hs);
		}
	}
	printf("%d\n",(int)c.size());
	ll tot=0;
	for(auto v:c1)
		tot+=v.second.size();
//	printf("%lld\n",tot);
	return 0;
}
