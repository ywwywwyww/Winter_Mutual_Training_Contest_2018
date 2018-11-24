#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<bitset>
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
int n,q;
char str[110][40];
namespace gao1
{
	ll s1[110];
	ll s2[110];
	void gao()
	{
		int ans=0;
		for(int i=1;i<=q;i++)
		{
			for(int j=1;j<=n;j++)
				if(str[i][j]=='1')
					s1[i]|=1<<(j-1);
				else if(str[i][j]=='0')
					s2[i]|=1<<(j-1);
		}
		for(int i=0;i<1<<n;i++)
		{
			for(int j=1;j<=q;j++)
				if(!(i&s2[j])&&!(((1<<n)-1-i)&s1[j]))
				{
					ans++;
					break;
				}
		}
		printf("%d\n",ans);
	}
}
int a0[110],a1[110],a2[110];
int b0[110],b1[110],b2[110];
const int A=10;
bitset<1<<A> s[110],ans[1<<(30-A)],c[1<<A];
int main()
{
	open("c");
	scanf("%d%d",&n,&q);
	for(int i=1;i<=q;i++)
		scanf("%s",str[i]+1);
	if(n<=A)
	{
		gao1::gao();
		return 0;
	}
	int Q=min(10,q);
	int N=n-A;
	int num=(q+Q-1)/Q;
	for(int i=1;i<=q;i++)
	{
		for(int j=1;j<=N;j++)
			if(str[i][j]=='?')
				a2[i]|=1<<(j-1);
			else if(str[i][j]=='1')
				a1[i]|=1<<(j-1);
			else
				a0[i]|=1<<(j-1);
		for(int j=1;j<=A;j++)
			if(str[i][j+N]=='?')
				b2[i]|=1<<(j-1);
			else if(str[i][j+N]=='1')
				b1[i]|=1<<(j-1);
			else
				b0[i]|=1<<(j-1);
		for(int j=0;j<1<<A;j++)
			if(!(j&b0[i])&&!(((1<<A)-1-j)&b1[i]))
				s[i].set(j);
	}
	for(int i=1;i<=num;i++)
	{
		int l=(i-1)*Q+1;
		int r=min(i*Q,q);
		for(int k=0;k<1<<(r-l+1);k++)
		{
			bitset<1<<A> temp;
			for(int j=1;j<=r-l+1;j++)
				if((k>>(j-1))&1)
					temp|=s[j+l-1];
			c[k]=temp;
		}
		for(int k=0;k<1<<N;k++)
		{
			int temp=0;
			for(int j=l;j<=r;j++)
				if(!(k&a0[j])&&!(((1<<N)-1-k)&a1[j]))
					temp|=1<<(j-l);
			ans[k]|=c[temp];
		}
	}
	int _=0;
	for(int i=0;i<1<<N;i++)
		_+=ans[i].count();
	printf("%d\n",_);
	return 0;
}
