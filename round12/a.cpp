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
const int N=200010;
int n;
char s[N];
int win(int first,int wr,int bl,ll s1,ll s2,int cnt1,int cnt2)
{
	assert(s1>=0);
	assert(s2>=0);
	int l=bl-wr;
	if(l&1)
	{
		if(first)
		{
			wr+=l/2;
			s1+=(ll)(cnt1-1)*(l/2);
			bl-=l/2-1;
			s2+=(ll)(cnt2-1)*(l/2-1);
		}
		else
		{
			wr+=l/2-1;
			s1+=(ll)(cnt1-1)*(l/2-1);
			bl-=l/2;
			s2+=(ll)(cnt2-1)*(l/2);
		}
		first^=1;
	}
	else
	{
		wr+=l/2-1;
		s1+=(ll)(cnt1-1)*(l/2-1);
		bl-=l/2-1;
		s2+=(ll)(cnt2-1)*(l/2-1);
	}
	if(first)
		if(s1<=s2)
			return 0;
		else
			return 1;
	else
		if(s2<=s1)
			return 1;
		else
			return 0;
}
int gao1()
{
	int wr=0,bl=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='W')
			wr=i;
		else if(s[i]=='B'&&!bl)
			bl=i;
	int first=1;
//	while(wr+2<bl)
//	{
//		if(!first)
//			wr++;
//		else
//			bl--;
//		first^=1;
//	}
	ll s1=0,s2=0;
	int cnt1=0,cnt2=0;
	for(int i=n;i>=1;i--)
		if(s[i]=='W')
		{
			cnt1++;
			s1+=wr-i-cnt1+1;
		}
	for(int i=1;i<=n;i++)
		if(s[i]=='B')
		{
			cnt2++;
			s2+=i-bl-cnt2+1;
		}
	return win(first,wr,bl,s1,s2,cnt1,cnt2);
//	if(first)
//		if(s1<=s2)
//			printf("B\n");
//		else
//			printf("W\n");
//	else
//		if(s2<=s1)
//			printf("W\n");
//		else
//			printf("B\n");
}
int gao2()
{
	int wr=0,bl=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='W')
			wr=i;
		else if(s[i]=='B'&&!bl)
			bl=i;
	ll s1=0,s2=0;
	int cnt1=0,cnt2=0;
	for(int i=n;i>=1;i--)
		if(s[i]=='W')
		{
			cnt1++;
			s1+=wr-i-cnt1+1;
		}
	for(int i=1;i<=n;i++)
		if(s[i]=='B')
		{
			cnt2++;
			s2+=i-bl-cnt2+1;
		}
	int wr2=0,bl2=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='B'&&i!=bl)
		{
			bl2=i;
			break;
		}
	for(int i=n;i>=1;i--)
		if(s[i]=='W'&&i!=wr)
		{
			wr2=i;
			break;
		}
	int first=1;
	while(1)
	{
		if(first)
		{
			if(cnt2==1)
				return 1;
			if(wr+1<bl2-1)
			{
				if(win(0,wr+1,bl2,s1+cnt1-1,s2-(cnt2-1)*(bl2-bl-1),cnt1,cnt2-1)==1)
					return 1;
			}
			else
			{
				if(!wr2)
					return 0;
				if(win(1,wr2,bl2-1,s1-(cnt1-1)*(wr-wr2-1),s2-(cnt2-1)*(bl2-bl-1)+(cnt2-2),cnt1-1,cnt2-1)==1)
					return 1;
			}
			if(cnt1==1)
				return 0;
			if(!s1)
				return 0;
			s1--;
			if(wr2<wr-1)
				wr2++;
		}
		else
		{
			if(cnt1==1)
				return 0;
			if(bl-1>wr2+1)
			{
				if(win(1,wr2,bl-1,s1-(cnt1-1)*(wr-wr2-1),s2+cnt2-1,cnt1-1,cnt2)==0)
					return 0;
			}
			else
			{
				if(!bl2)
					return 1;
				if(win(0,wr2+1,bl2,s1-(cnt1-1)*(wr-wr2-1)+(cnt1-2),s2-(cnt2-1)*(bl2-bl-1),cnt1-1,cnt2-1)==0)
					return 0;
			}
			if(cnt2==1)
				return 1;
			if(!s2)
				return 1;
			s2--;
			if(bl2>bl+1)
				bl2--;
		}
		first^=1;
	}
	return 1;
}
void solve()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	int wr=0,bl=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='W')
			wr=i;
		else if(s[i]=='B'&&!bl)
			bl=i;
	int ans;
	if(wr+1<bl)
		ans=gao1();
	else
		ans=gao2();
	if(ans)
		printf("W\n");
	else
		printf("B\n");
}
int main()
{
	open("a");
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
