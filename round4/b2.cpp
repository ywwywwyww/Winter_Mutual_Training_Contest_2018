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
const int N=100010;
int l[N],r[N];
int n;
ll prew[N],w[N],pred[N],d[N];
int b[N];
int main()
{
	freopen("b.in","r",stdin);
	freopen("b2.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		l[i]<<=1;
		r[i]<<=1;
	}
	for(int i=1;i<=n;i++)
	{
		w[i]=r[i]-l[i];
		d[i]=(ll)w[i]*(l[i]+r[i])/2;
		prew[i]=w[i]+prew[i-1];
		pred[i]=d[i]+pred[i-1];
	}
	int last=0;
	int ans=0;
	for(int i=1;i<=n;i++)
		b[i]=1;
	for(int i=1;i<n;i++)
		for(int j=1;j<i;j++)
			if(l[i+1]*(prew[i]-prew[j])>pred[i]-pred[j]||r[i+1]*(prew[i]-prew[j])<pred[i]-pred[j])
				b[j]=0;
	for(int i=1;i<=n;i++)
		if(b[i])
		{
			ans=max(ans,i-last);
			last=i;
		}
	printf("%d\n",ans);
	return 0;
}
