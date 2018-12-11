#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<queue>
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
const int N=100010;
int n,m,s;
int a[N];
priority_queue<int> q;
priority_queue<int,vector<int>,greater<int> > q2;
ll gao()
{
	if(s==1)
		return 0x7fffffffffffffffll;
	ll res=0;
	int t=m;
	if(s!=n)
	{
		res+=2*(a[n]-a[s]);
		t=min(t,s-1);
	}
	ll tot=0;
	int sz=0;
	ll temp=res;
	res=0x7fffffffffffffffll;
	while(!q.empty())
		q.pop();
	while(!q2.empty())
		q2.pop();
	for(int i=s-1;i>=1;i--)
	{
		if(i+1<s-1)
		{
			sz++;
			tot+=a[i+2]-a[i+1];
			q.push(a[i+2]-a[i+1]);
		}
		int z=s-i;
		while(z>=t&&sz>z-t)
		{
			int v=q.top();
			q.pop();
			tot-=v;
			sz--;
			q2.push(v);
		}
		while(!q.empty()&&!q2.empty()&&q.top()>q2.top())
		{
			int v1=q.top();
			int v2=q2.top();
			q.pop();
			q2.pop();
			q.push(v2);
			q2.push(v1);
			tot-=v1;
			tot+=v2;
		}
		if(z-sz==t)
			res=min(res,temp+a[i]-a[1]+a[s]-a[1]+2*tot);
	}
	return res;
}
int main()
{
	open("a");
	scanf("%d%d%d",&n,&m,&s);
	if(m==0&&s!=1)
	{
		printf("-1\n");
		return 0;
	}
	if(m==n-1&&s!=n)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	ll ans=0x7fffffffffffffffll;
	ans=min(ans,gao());
	int tot=a[n];
	reverse(a+1,a+n+1);
	s=n-s+1;
	m=n-1-m;
	for(int i=1;i<=n;i++)
		a[i]=tot-a[i];
	ans=min(ans,gao());
	printf("%lld\n",ans);
	return 0;
}
