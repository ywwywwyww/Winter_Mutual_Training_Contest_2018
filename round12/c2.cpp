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
//typedef double ll;
int n,k;
ll p;
void add(ll &a,ll b)
{
//	a+=b;
	a=(a+b)%p;
}
ll f[100][10][10][10][10][10][10];
bool b[10][10][10][10][10][10];
int t;
int a[50000][100];
int main()
{
	freopen("c.in","r",stdin);
	freopen("c2.out","w",stdout);
	scanf("%d%d%lld",&n,&k,&p);
	f[0][0][0][0][0][0][0]=1;
	for(int i=0;i<n;i++)
		for(int ab=0;ab<=k;ab++)
			for(int ba=0;ba<=k;ba++)
				for(int ac=0;ac<=k;ac++)
					for(int ca=0;ca<=k;ca++)
						for(int bc=0;bc<=k;bc++)
							for(int cb=0;cb<=k;cb++)
							{
								add(f[i+1][ab+1][max(ba-1,0)][ac+1][max(ca-1,0)][bc][cb],f[i][ab][ba][ac][ca][bc][cb]);
								add(f[i+1][max(ab-1,0)][ba+1][ac][ca][bc+1][max(cb-1,0)],f[i][ab][ba][ac][ca][bc][cb]);
								add(f[i+1][ab][ba][max(ac-1,0)][ca+1][max(bc-1,0)][cb+1],f[i][ab][ba][ac][ca][bc][cb]);
							}
	for(int i=1;i<=n;i++)
	{
		ll ans=0;
		int cnt=0;
		for(int ab=0;ab<=k;ab++)
			for(int ba=0;ba<=k;ba++)
				for(int ac=0;ac<=k;ac++)
					for(int ca=0;ca<=k;ca++)
						for(int bc=0;bc<=k;bc++)
							for(int cb=0;cb<=k;cb++)
							{
								add(ans,f[i][ab][ba][ac][ca][bc][cb]);
								if(i==n&&b[ab][ba][ac][ca][bc][cb])
									continue;
								if(f[i][ab][ba][ac][ca][bc][cb])
								{
									cnt++;
									if(i==n)
									{
//										printf("%d %d %d %d %d %d\n",ab,ba,ac,ca,bc,cb);
										b[ab][ba][ac][ca][bc][cb]=1;//abc
										b[ac][ca][ab][ba][cb][bc]=1;//abc
										b[ba][ab][bc][cb][ac][ca]=1;//bac
										b[bc][cb][ba][ab][ca][ac]=1;//bca
										b[ca][ac][cb][bc][ab][ba]=1;//cab
										b[cb][bc][ca][ac][ba][ab]=1;//cba
										int flag=1;
										for(int k=1;k<=t;k++)
										{
											int flag2=1;
											for(int l=1;l<=n;l++)
												if(a[k][l]!=f[l][ab][ba][ac][ca][bc][cb])
												{
													flag2=0;
													break;
												}
											if(flag2)
											{
												flag=0;
												break;
											}
										}
										if(flag)
										{
											t++;
											for(int l=1;l<=n;l++)
												a[t][l]=f[l][ab][ba][ac][ca][bc][cb];
										}
									}
								}
							}
		printf("%lld\n",ans);
//		printf("%d %lld\n",cnt,ans);
//		printf("%.10f\n",ans);
	}
	printf("%d\n",t);
	return 0;
}
