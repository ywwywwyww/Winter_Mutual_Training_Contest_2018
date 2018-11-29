#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)x.size())
#define L(i,u) for (register int i=head[u]; i; i=nxt[i])
#define rep(i,a,b) for (register int i=(a); i<=(b); i++)
#define per(i,a,b) for (register int i=(a); i>=(b); i--)
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef pair<int,int> Pii;
typedef vector<int> Vi;
inline void read(int &x) {
	x=0; char c=getchar(); int f=1;
	while (!isdigit(c)) {if (c=='-') f=-1; c=getchar();}
	while (isdigit(c)) {x=x*10+c-'0'; c=getchar();} x*=f;
}
const int N = 1000000,mo=998244353;const ll M = 1LL*mo*mo;
int n,fac[N],ifac[N],mi[N];
int x[N],y[N];int f[N],g[N];
int power(int a, int n){
	int res=1;
	while(n){
		if(n&1)res=1LL*res*a%mo;
		a=1LL*a*a%mo;n>>=1;
	}
	return res;
}
inline int C(int n, int m){return m>=0&&m<=n?1LL*fac[n]*ifac[m]%mo*ifac[n-m]%mo:0;}
inline ll vio(int x1, int y1, int x2, int y2){//(x1<=x2)
	x2-=x1;y2-=y1;return x2>=0&&y2>=0?C(x2+y2,x2):0;
}
inline ll vio1(int x1, int y1, int x2, int y2){//(x1<=x2)
	x2-=x1;y2-=y1;return x2>=0&&y2>=0?1LL*C(x2+y2,x2)*(mi[x2+y2+1]-1)%mo:0;
}
ll getqz(int n, int m){return C(n+1+m+1,m+1)-1;}

int w[N],F[N],G[N],H[N];
inline void fft(int *a, int n, int tp){
	for(int i=1,j=0;i<n;i++){
		for(int k=n>>1;!((j^=k)&k);k>>=1);if(i<j)swap(a[i],a[j]);
	}
	for(int j=2;j<=n;j<<=1){
		w[0]=1;w[1]=power(3,(mo-1)/j);if(tp==-1)w[1]=power(w[1],mo-2);
		rep(i,2,(j>>1)-1)w[i]=1LL*w[i-1]*w[1]%mo;
		for(int k=0;k<n;k+=j)rep(i,0,(j>>1)-1){
			int x=a[k+i],y=1LL*a[k+i+(j>>1)]*w[i]%mo;
			a[k+i]=x+y<mo?x+y:x+y-mo;a[k+i+(j>>1)]=x-y>=0?x-y:x-y+mo;
		}
	}
}
inline void mul(int *a, int *b, int l1, int l2, int *c){
	if(1LL*l1*l2<=6000){
		rep(i,0,l1+l2){
			ll t=0;int lim=min(i,l1);rep(j,max(0,i-l2),lim){t+=1LL*a[j]*b[i-j];t=t<M?t:t-M;}
			c[i]=t%mo;
		}
		return;
	}
	int n;for(n=1;n<=l1+l2;n<<=1);
	rep(i,l1+1,n-1)a[i]=0;rep(i,l2+1,n-1)b[i]=0;
	fft(a,n,1);fft(b,n,1);
	rep(i,0,n-1)a[i]=1LL*a[i]*b[i]%mo;
	fft(a,n,-1);int ni=power(n,mo-2);
	rep(i,0,l1+l2)c[i]=1LL*a[i]*ni%mo;
	
//	fft(c,n,1);fft(c,n,-1);rep(i,0,n-1)c[i]=1LL*c[i]*ni;
}
inline void solve(int *a, int l1, int *b, int l2, int d){
	if(d<0)return;
	rep(i,0,l1)F[i]=a[i];rep(i,0,l2)G[i]=1LL*fac[d+i]*ifac[i]%mo;
	mul(F,G,l1,l2,H);rep(i,0,l2)b[i]=(b[i]+1LL*H[i]*ifac[d])%mo;
}
inline void solve1(int *a, int l1, int *b, int l2, int d){
	if(d<0)return;
	rep(i,0,l1)F[i]=a[i];rep(i,0,l2)G[i]=1LL*fac[d+i]*ifac[i]%mo*(mi[d+i+1]-1)%mo;
	mul(F,G,l1,l2,H);rep(i,0,l2)b[i]=(b[i]+1LL*H[i]*ifac[d])%mo;
}
inline void solve2(int *a, int l1, int *b, int l2, int c, int d){
	if(c<0||d<0)return;
	rep(i,0,l1)F[i]=1LL*a[i]*ifac[c+l1-i]%mo;rep(i,0,l1+l2)G[i]=fac[d+c+i];
	mul(F,G,l1,l1+l2,H);rep(i,0,l2)b[i]=(b[i]+1LL*H[l1+i]*ifac[d+i])%mo;
}
inline void solve3(int *a, int l1, int *b, int l2, int c, int d){
	if(c<0||d<0)return;
	rep(i,0,l1)F[i]=1LL*a[i]*ifac[c+l1-i]%mo;rep(i,0,l1+l2)G[i]=1LL*fac[d+c+i]*(mi[d+c+i+1]-1)%mo;
	mul(F,G,l1,l1+l2,H);rep(i,0,l2)b[i]=(b[i]+1LL*H[l1+i]*ifac[d+i])%mo;
}
int main() {//freopen("1.in","r",stdin);
freopen("c.in","r",stdin);
freopen("c3.out","w",stdout);
	int mx=N-2;fac[0]=1;rep(i,1,mx)fac[i]=1LL*fac[i-1]*i%mo;
	ifac[mx]=power(fac[mx],mo-2);per(i,mx-1,0)ifac[i]=1LL*ifac[i+1]*(i+1)%mo;
	mi[0]=1;rep(i,1,mx)mi[i]=2LL*mi[i-1]%mo;
	int qq;read(qq);read(qq);read(n);
	rep(i,0,n+1)rep(j,0,1)read(x[i*2+j]),read(y[i*2+j]);
	/*if(!n){
		ll res=0;
		int x0[2],y0[2],x1[2],y1[2];
		x0[0]=x[1];x0[1]=x[0]-1;y0[0]=y[1];y0[1]=y[0]-1;
		x1[0]=x[2];x1[1]=x[3]+1;y1[0]=y[2];y1[1]=y[3]+1;
		rep(i,0,1)rep(j,0,1)rep(k,0,1)rep(l,0,1)
			res+=vio(x0[i],y0[j],x1[k],y1[l])*((i+j+k+l)&1?-1:1);
		cout<<(res%mo+mo)%mo;
		return 0;
	}*/
	rep(i,y[0],y[1])f[i]=getqz(x[1]-x[0],i-y[0]);
	rep(i,x[0],x[1])g[i]=getqz(i-x[0],y[1]-y[0]);
	rep(t,2,2*n+2)
		if(t&1){
			static int a[N],b[N];rep(i,y[t-1],y[t])a[i]=0;rep(i,x[t-1],x[t])b[i]=0;
		//	rep(i,y[t-1],y[t])rep(j,y[t-1],y[t])a[i]=(a[i]+f[j]*vio1(x[t-1],j,x[t],i))%mo;
			solve1(f+y[t-1],y[t]-y[t-1],a+y[t-1],y[t]-y[t-1],x[t]-x[t-1]);
			
		//	rep(i,y[t-1],y[t])rep(j,x[t-1],x[t])a[i]=(a[i]+g[j]*vio1(j,y[t-1],x[t],i))%mo;
			solve3(g+x[t-1],x[t]-x[t-1],a+y[t-1],y[t]-y[t-1],0,0);
		
		//	rep(i,x[t-1],x[t])rep(j,y[t-1],y[t])b[i]=(b[i]+f[j]*vio1(x[t-1],j,i,y[t]))%mo;
			solve3(f+y[t-1],y[t]-y[t-1],b+x[t-1],x[t]-x[t-1],0,0);
		//	rep(i,x[t-1],x[t])rep(j,x[t-1],x[t])b[i]=(b[i]+g[j]*vio1(j,y[t-1],i,y[t]))%mo;
			solve1(g+x[t-1],x[t]-x[t-1],b+x[t-1],x[t]-x[t-1],y[t]-y[t-1]);
			rep(i,y[t-1],y[t])f[i]=a[i];rep(i,x[t-1],x[t])g[i]=b[i];
		//	rep(i,y[t-1],y[t])printf("%d %d:%d\n",t,i,f[i]);
		//	rep(i,x[t-1],x[t])printf("%d %d:%d\n",t,i,g[i]);
		}
		else{
			static int a[N],b[N];rep(i,y[t],y[t+1])a[i]=0;rep(i,x[t],x[t+1])b[i]=0;
		//	rep(i,y[t-2],y[t-1])printf("%d %d:%d\n",t,i,f[i]);
		//	rep(i,x[t-2],x[t-1])printf("%d %d:%d\n",t,i,g[i]);
		//	rep(i,y[t],y[t+1])rep(j,y[t-2],y[t-1])a[i]=(a[i]+f[j]*vio(x[t-1]+1,j,x[t]-1,i))%mo;
			solve(f+y[t-2],y[t-1]-y[t-2],a+y[t-2],y[t+1]-y[t-2],x[t]-1-x[t-1]-1);
			
			
		//	rep(i,y[t],y[t+1])rep(j,x[t-2],x[t-1])a[i]=(a[i]+g[j]*vio(j,y[t-1]+1,x[t]-1,i))%mo;
			solve2(g+x[t-2],x[t-1]-x[t-2],a+y[t],y[t+1]-y[t],x[t]-1-x[t-1],y[t]-y[t-1]-1);
			
			
		//	rep(i,x[t],x[t+1])rep(j,y[t-2],y[t-1])b[i]=(b[i]+f[j]*vio(x[t-1]+1,j,i,y[t]-1))%mo;
			solve2(f+y[t-2],y[t-1]-y[t-2],b+x[t],x[t+1]-x[t],y[t]-1-y[t-1],x[t]-x[t-1]-1);
			
		//	rep(i,x[t],x[t+1])rep(j,x[t-2],x[t-1])b[i]=(b[i]+g[j]*vio(j,y[t-1]+1,i,y[t]-1))%mo;
			solve(g+x[t-2],x[t-1]-x[t-2],b+x[t-2],x[t+1]-x[t-2],y[t]-1-y[t-1]-1);
			rep(i,y[t],y[t+1])f[i]=a[i];rep(i,x[t],x[t+1])g[i]=b[i];
		//	rep(i,y[t],y[t+1])printf("%d %d:%d\n",t,i,f[i]);
		//	rep(i,x[t],x[t+1])printf("%d %d:%d\n",t,i,g[i]);
		}
	ll res=0;
	rep(i,y[2*n+2],y[2*n+3])res=(res+getqz(x[2*n+3]-x[2*n+2],y[2*n+3]-i)*f[i])%mo;
	rep(i,x[2*n+2],x[2*n+3])res=(res+getqz(x[2*n+3]-i,y[2*n+3]-y[2*n+2])*g[i])%mo;
	cout<<(res%mo+mo)%mo;
	return 0;
}
