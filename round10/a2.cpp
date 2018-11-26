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
typedef __int128 lll;
const int N=100010;
ll f[N],l[N],t[N],w[N],s[N];
int n;
int main()
{
	freopen("a.in","r",stdin);
	freopen("a2.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		l[i]=rd();
		t[i]=rd();
		w[i]=rd();
		s[i]=s[i-1]+w[i];
	}
	for(int i=1;i<=n;i++)
	{
		f[i]=1e18;
		ll ma=t[i];
		for(int j=i;j>l[i];j--)
		{
			ma=max(ma,t[j]);
			f[i]=min(f[i],f[j-1]+ma*(s[n]-s[i]));
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}
