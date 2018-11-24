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
const int N=200010;
ll f[N];
char s[N];
int fail[N];
int main()
{
	freopen("c.in","r",stdin);
	freopen("c2.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		fail[1]=0;
		f[i]=(f[i]+f[i-1])%p;
		for(int j=i+1;j<=n;j++)
		{
			fail[j-i+1]=fail[j-i];
			while(fail[j-i+1]&&s[i+fail[j-i+1]]!=s[j])
				fail[j-i+1]=fail[fail[j-i+1]];
			if(s[i+fail[j-i+1]]==s[j])
				fail[j-i+1]++;
			int v;
			if((j-i+1)%(j-i+1-fail[j-i+1])==0)
				v=(j-i+1)/(j-i+1-fail[j-i+1]);
			else
				v=1;
			f[j]=(f[j]+f[i-1]*(v&1?1:-1))%p;
		}
	}
	ll ans=(f[n]+p)%p;
	printf("%lld\n",ans);
	return 0;
}
