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
int c[1010][1010];
int pw[1010];
int main()
{
	for(int i=0;i<=1000;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	pw[0]=1;
	for(int i=1;i<=100;i++)
		pw[i]=pw[i-1]*2;
	for(int i=0;i<=10;i++)
	{
		for(int j=0;j<=i;j++)
		{
			int s=0;
			for(int k=0;k<=j;k++)
				for(int l=0;l<=i-j;l++)
					s+=c[k+l][k]*pw[k]*pw[l];
			printf("%d ",s);
		}
	}
	return 0;
}
