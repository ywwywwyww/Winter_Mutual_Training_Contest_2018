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
int f[20][2][1<<17];
char s[100000];
int n;
int dfs(int x,int v,int first)
{
	if(~f[x][first][v])
		return f[x][first][v];
	int &res=f[x][first][v];
	int a[20],b[20];
	for(int i=1;i<=n;i++)
		if((v>>(i-1))&1)
			if(i<=x)
				a[i]=1;
			else
				a[i]=2;
		else
			a[i]=0;
	for(int i=1;i<=n;i++)
		if(a[i]&&a[i]==(first^1)+1)
		{
			memcpy(b,a,sizeof a);
			if(b[i]==1)
			{
				if(b[i+1]==b[i])
					continue;
				b[i+1]=b[i];
				b[i]=0;
			}
			else
			{
				if(b[i-1]==b[i])
					continue;
				b[i-1]=b[i];
				b[i]=0;
			}
			int wr=0;
			for(int i=n;i>=1;i--)
				if(b[i]==1)
				{
					wr=i;
					break;
				}
			int cnt1=0,cnt2=0;
			int v2=0;
			for(int i=1;i<=n;i++)
			{
				if(b[i])
					v2|=1<<(i-1);
				if(b[i]==1)
					cnt1++;
				else if(b[i]==2)
					cnt2++;
			}
			if(!cnt1)
				return res=0;
			if(!cnt2)
				return res=1;
			if(dfs(wr,v2,first^1)==first)
				return res=first;
	}
	return res=first^1;
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("a2.out","w",stdout);
	int t=rd();
	while(t--)
	{
		memset(f,-1,sizeof f);
		scanf("%s",s+1);
		n=strlen(s+1);
		int v=0;
		for(int i=1;i<=n;i++)
			if(s[i]!='.')
				v|=1<<(i-1);
		int wr;
		for(int i=n;i>=1;i--)
			if(s[i]=='W')
			{
				wr=i;
				break;
			}
		if(dfs(wr,v,1)==1)
			printf("W\n");
		else
			printf("B\n");
	}
	return 0;
}
