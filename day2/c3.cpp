#include  <bits/stdc++.h>
using namespace std;

const int RLEN=1<<18|1;
inline char nc() {
	static char ibuf[RLEN],*ib,*ob;
	(ib==ob) && (ob=(ib=ibuf)+fread(ibuf,1,RLEN,stdin));
	return (ib==ob) ? -1 : *ib++;
}
inline int rd() {
	char ch=nc(); int i=0,f=1;
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=nc();}
	while(isdigit(ch)) {i=(i<<1)+(i<<3)+ch-'0'; ch=nc();}
	return i*f;
}

const int N=1e6+50;
int n,m,h,p,a,b,c;
int f[N],g[N],S[N],iv[N],bp[N],hp[N],ans;
inline int add(int x,int y) {return (x+y>=p) ? (x+y-p) : (x+y);}
inline int dec(int x,int y) {return (x-y<0) ? (x-y+p) : (x-y);}
inline int mul(int x,int y) {return (long long)x*y%p;}
inline int power(int a,int b,int rs=1) {for(;b;b>>=1,a=mul(a,a)) if(b&1) rs=mul(rs,a); return rs;}
inline int inv(int a) {return power(a,p-2);}

inline void init() {
	rd();
	n=rd(), m=rd(), h=rd(), p=rd();
	h%=p, b=rd()%p, a=rd()%p, c=rd()%p; 
	m--; n--;
}
inline int ss(int x,int y,int z) {
	if(x==1) return (z+1-y)%p;
	return mul(dec(power(x,z+1),power(x,y)),inv(dec(x,1)));
}
int main() {
	freopen("c.in","r",stdin);
	freopen("c3.out","w",stdout);
	init();
	iv[1]=1;
	for(int i=2;i<=n+10;i++) iv[i]=mul(p-p/i,iv[p%i]);
	hp[0]=1; int st=power(h,m+1);
	for(int i=1;i<=n+10;i++) hp[i]=mul(hp[i-1],st);
	bp[0]=1;
	for(int i=1;i<=n+10;i++) bp[i]=mul(bp[i-1],b);
	if(!h) {cout<<add(c,mul(a,rd()))<<'\n'; return 0;}
	if(a!=1) {
		a=mul(a,h);
		f[0]=mul(dec(power(a,m+1),1),inv(dec(a,1)));
		int C=power(a,m+1), ia=inv(dec(1,a));
		for(int i=1;i<=n;i++) {
			C=mul(C,mul(i+m,iv[i]));
			f[i]=mul(ia,dec(f[i-1],C));
		}
		for(int i=0;i<=n;i++) {
			S[i]=mul(bp[i],f[i]);
			S[i]=mul(S[i],hp[i]);
			S[i]=add(S[i],i?S[i-1]:0);
		}
		for(int i=n;~i;i--) ans=add(ans,mul(mul(S[i],hp[n-i]),rd()));	
		ans=mul(ans,mul(a,inv(h)));
		for(int i=0;i<=n;i++) {
			S[i]=mul(bp[i],f[i]);
			S[i]=add(S[i],i?S[i-1]:0);
		}
		g[0]=ss(a,0,m); g[0]=mul(g[0],mul(a,inv(h)));
		g[0]=dec(g[0],ss(h,0,m)); g[0]=mul(g[0],inv(dec(mul(a,inv(h)),1)));
		ans=add(ans,mul(g[0],c));
		a=mul(a,inv(h)); ia=inv(dec(1,a));
		int val=ss(h,0,m);
		for(int i=1;i<=n;i++) {
			g[i]=dec(mul(g[i-1],b),mul(a,S[i]));
			g[i]=add(g[i],val);
			g[i]=mul(g[i],ia);
			ans=add(ans,mul(mul(g[i],hp[i]),c));
		}
	} else {
		int C=power(h,m+1);
		if(h==1) {
			for(int i=1;i<=n+2;i++) {
				C=mul(C,mul(i+m,iv[i]));
				f[i-1]=C;
			}
		} else {
			f[0]=mul(dec(power(h,m+1),1),inv(dec(h,1)));
			int ia=inv(dec(1,h));
			for(int i=1;i<=n+1;i++) {
				C=mul(C,mul(i+m,iv[i]));
				f[i]=mul(ia,dec(f[i-1],C));
			}	
		}
		for(int i=0;i<=n;i++) {
			S[i]=mul(bp[i],f[i]);
			S[i]=mul(S[i],hp[i]);
			S[i]=add(S[i],i?S[i-1]:0);
		}
		for(int i=n;i>=0;i--) ans=add(ans,mul(mul(S[i],hp[n-i]),rd()));
		if(b) {
			for(int i=1;i<=n+1;i++) f[i]=add(mul(f[i],bp[i]),f[i-1]);
			int ia=inv(b), val=ss(h,0,m);
			for(int i=0;i<=n;i++) {
				int s=dec(f[i+1],val);
				s=mul(s,ia);
				ans=add(ans,mul(mul(s,hp[i]),c));
			}
		} else {
			int s;
			if(h==1) s=1ll*(m+2)*(m+1)/2%p;
			else s=mul(m+1,power(h,m+1)), s=dec(s,ss(h,0,m)), s=mul(s,inv(dec(h,1)));
			int st=power(h,m+1);
			for(int i=0,j=1;i<=n;i++) ans=add(ans,mul(c,mul(s,j))), j=mul(j,st);
		}
	} cout<<(ans%p+p)%p<<'\n';
}
