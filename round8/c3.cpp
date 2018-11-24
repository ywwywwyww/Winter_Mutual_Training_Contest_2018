#include<bits/stdc++.h>
using namespace std;
namespace FFT{
	#define mod 998244353
	#define G 3
	#define maxn 501000
	typedef long long ll;
	int bh[maxn],tmpA[maxn],tmpB[maxn],tmpC[maxn],tmp[maxn],lim=maxn,w[2][maxn];
	int qpow(int a,int b){
		int ans=1,tmp=a;
		for(;b;b>>=1,tmp=1ll*tmp*tmp%mod)
			if(b&1)ans=1ll*ans*tmp%mod;
		return ans;
	}
	void init(int b){
		for(int i=1;i<(1<<b);i<<=1){
			int wn=qpow(G,(mod-1)/(i<<1));
			for(int j=0;j<i;++j)w[1][i+j]=(j?1ll*wn*w[1][i+j-1]%mod:1);
			wn=qpow(G,mod-1-(mod-1)/(i<<1));
			for(int j=0;j<i;++j)w[0][i+j]=(j?1ll*wn*w[0][i+j-1]%mod:1);
		}
	}
	ll gmod(ll x){
		return x>=mod?x-mod:x;
	}
	void fft(int h[],int len,int flag){
		if(flag==-1)flag=0;
		for(int i=0,j=0;i<len;++i){
			if(i<j)swap(h[i],h[j]);
			for(int k=len>>1;(j^=k)<k;k>>=1);
		}
		for(int i=1;i<len;i<<=1)
			for(int j=0;j<len;j+=(i<<1))
				for(int k=0;k<i;++k){
					int x=h[j+k],y=(ll)h[j+k+i]*w[flag][i+k]%mod;
					h[j+k]=gmod((ll)x+y);
					h[j+k+i]=gmod((ll)x-y+mod);
				}
		if(flag==0){
			int x=qpow(len,mod-2);
			for(int i=0;i<len;++i)
				h[i]=1ll*h[i]*x%mod;
		}
	}
	void poly_mul(const int A[],int lenA,const int B[],int lenB,int C[],int lenc){
		int l=1,k=0,L=min(lenA,lenc)+min(lenB,lenc)+1;
		if(1ll*lenA*lenB<=400){
			for(int i=0;i<L;++i)tmpA[i]=0;
			for(int i=0;i<lenA;++i)if(A[i])
				for(int j=0;j<lenB;++j)if(B[j])
					tmpA[i+j]=(tmpA[i+j]+1ll*A[i]*B[j])%mod;
			for(int i=0;i<lenc&&i<L;++i)C[i]=tmpA[i];
			for(int i=L;i<lenc;++i)C[i]=0;
			return ;
		}
		while(l<L)l<<=1,k++;
		memset(tmpA,0,l<<2);
		memset(tmpB,0,l<<2);
		memcpy(tmpA,A,min(lenA,lenc)<<2);
		memcpy(tmpB,B,min(lenB,lenc)<<2);
		fft(tmpA,l,1),fft(tmpB,l,1);
		for(int i=0;i<l;++i)tmpA[i]=1ll*tmpA[i]*tmpB[i]%mod;
		fft(tmpA,l,-1);
		for(int i=0;i<lenc&&i<L;++i)C[i]=tmpA[i];
		for(int i=L;i<lenc;++i)C[i]=0;
	}
	void poly_inv(int n,const int a[],int C[]){
		if(n==1){
			C[0]=qpow(a[0],mod-2);
			return ;
		}
		static int A[maxn];
		A[0]=qpow(a[0],mod-2);
		int m=(n+1)/2,len=1,k=0;
		poly_inv(m,a,C);
		while(len<n+n)len<<=1,k++;
		memcpy(A,a,n<<2);
		memset(A+n,0,(len-n)<<2);
		memset(C+m,0,(len-m)<<2);
		fft(A,len,1),fft(C,len,1);
		for(int i=0;i<len;++i)C[i]=1ll*(2ll-1ll*A[i]*C[i]%mod+mod)*C[i]%mod;
		fft(C,len,-1);
	}
	
	void poly_div(const int a[],int lena,const int b[],int lenb,int C[],int& plen){
		static int A[maxn],B[maxn];
		while(!a[lena-1]&&lena>=1)lena--;
		while(!b[lenb-1]&&lenb>=1)lenb--;
		if(lena<lenb){
			plen=1,C[0]=0;
			return ;
		}
		plen=lena-lenb+1;
		memcpy(A,a,lena<<2);
		memcpy(B,b,lenb<<2);
		reverse(A,A+lena);
		reverse(B,B+lenb);
		poly_inv(plen,B,tmp);
		poly_mul(tmp,plen,A,lena,C,plen);
		reverse(C,C+plen);
	}
	typedef vector<int> Poly;
	int SZ(const Poly& v){return v.size();}
	void upd(Poly& v){while(v.size()>1&&!v.back())v.pop_back();}
	Poly operator*(const Poly& a,const Poly& b){
		Poly ret(SZ(a)+SZ(b)-1);
		poly_mul(a.data(),SZ(a),b.data(),SZ(b),ret.data(),SZ(ret));
		upd(ret);
		return ret;
	}
	Poly operator/(const Poly& a,const Poly& b){
		int len;
		poly_div(a.data(),SZ(a),b.data(),SZ(b),tmp,len);
		Poly ret=Poly(tmp,tmp+len);
		upd(ret);
		return ret;
	}
	Poly operator-(const Poly& a,const Poly& b){
		Poly ret(max(SZ(a),SZ(b)));
		for(int i=0;i<SZ(ret);++i)
			ret[i]=(1ll*(i<SZ(a)?a[i]:0)-(i<SZ(b)?b[i]:0)+mod)%mod;
		upd(ret);
		return ret;
	}
	Poly operator+(const Poly& a,const Poly& b){
		Poly ret(max(SZ(a),SZ(b)));
		for(int i=0;i<SZ(ret);++i)
			ret[i]=(1ll*(i<SZ(a)?a[i]:0)+(i<SZ(b)?b[i]:0))%mod;
		upd(ret);
		return ret;
	}
	Poly operator%(const Poly& a,const Poly& b){
		int len;
		poly_div(a.data(),SZ(a),b.data(),SZ(b),tmp,len);
		poly_mul(b.data(),SZ(b),tmp,len,tmp,SZ(a));
		for(int i=0;i<SZ(a);++i)
			tmp[i]=(1ll*a[i]-tmp[i]+mod)%mod;
		for(len=SZ(a);len>1&&!tmp[len-1];len--);
		return Poly(tmp,tmp+len);
	}
	void print(const Poly& x){
		printf("\n[len=%d]",SZ(x));
		for(int i=0;i<SZ(x);++i)
			printf("%d ",x[i]);
		puts("");
	}
	
	Poly getinv(Poly g,int n){
		for(int i=0;i<n;++i)tmpC[i]=0;
		for(int i=0;i<g.size()&&i<n;++i)tmpC[i]=g[i];
		poly_inv(n,tmpC,tmp);
		return Poly(tmp,tmp+n); 
	}
	#undef maxn
	#undef G
	#undef mod
};
using namespace FFT;
const int mod=998244353;
const int maxn=1.2e5+100;
int a[maxn],b[maxn],f[maxn],g[maxn],n,asz,bsz;
int fac[maxn],inv[maxn];
// f(i)=[i-1 \in B]+\sum(j\in A)(j=1..i-1) C(i-1,j) g(i-1-j)
// g(i)=\sum_{j=2}^{i} C(i-1,j-1) f(j) g(i-j)
void solve(int l,int r){
	if(l==r){
		if(!l)return ;
		f[l]=(1ll*f[l]*fac[l-1]+b[l-1]-(a[l-1]?1:0)+mod)%mod;
		g[l]=(1ll*g[l]*fac[l-1]%mod+(l>=2?f[l]:0))%mod;
//		printf("[%d:(%d,%d)]\n",l,f[l],g[l]);
		return ;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
//	if(r-l>mid)printf("{%d,%d}",l,r);
	Poly L(mid-l+1),R(r-l+1);
//	printf("[%d,%d]->[%d,%d]\n",l,mid,mid+1,r);
	for(int i=l;i<=mid;++i)L[i-l]=1ll*g[i]*inv[i]%mod;
	for(int i=0;i<=r-l;++i)if(a[i])R[i]=inv[i];
	Poly s1=L*R;
	for(int i=mid+1;i<=r;++i)f[i]=(f[i]+s1[i-l-1])%mod;
	
	//g[l....mid]* f[2...min(r-l,mid)]
	L=Poly(mid-l+1),R=Poly(min(r-l,mid)+1);
	for(int i=l;i<=mid;++i)L[i-l]=1ll*g[i]*inv[i]%mod;
	for(int i=2;i<=min(r-l,mid);++i)R[i]=1ll*f[i]*inv[i-1]%mod;
	s1=L*R;
	for(int i=mid+1;i<=r;++i)if(i-l<s1.size())g[i]=(g[i]+s1[i-l])%mod;
	
	//f[max(2,l)...mid]* g[1...l-1]
//	if(l-1>=r-mid){
		L=Poly(mid-l+1),R=Poly(min(r-l,l-1)+1);
		for(int i=max(2,l);i<=mid;++i)L[i-l]=1ll*f[i]*inv[i-1]%mod;
		for(int i=0;i<=min(r-l,l-1);++i)R[i]=1ll*g[i]*inv[i]%mod;
		s1=L*R;
		for(int i=mid+1;i<=r;++i)if(i-l<s1.size())g[i]=(g[i]+s1[i-l])%mod;
//	}
	solve(mid+1,r);
}
int C(int x,int y){
	if(x<y||y<0)return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
	freopen("c.in","r",stdin);
	freopen("c3.out","w",stdout);
	FFT::init(18);
	scanf("%d%d%d",&n,&asz,&bsz);
	for(int i=1,x;i<=asz;++i)scanf("%d",&x),a[x]=1;
	for(int i=1,x;i<=bsz;++i)scanf("%d",&x),b[x]=1;
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);
	for(int i=n-1;i>=0;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	b[0]=1;
	/*
	f[0]=g[0]=1;
	for(int i=1;i<=n;++i){
		f[i]=b[i-1];//j==i-1? C(i-1,i-1)*g[0]
		for(int j=0;j<=i-2;++j) //g[1]....g[i-2] g[1]*C(i-1,i-2) a[i-2]
			if(a[j])f[i]=(f[i]+1ll*C(i-1,j)*g[i-1-j])%mod;
		for(int j=2;j<=i;++j)//j=i-1:g[i]=f[i-1]*(i-1)
			g[i]=(g[i]+1ll*C(i-1,j-1)*f[j]%mod*g[i-j])%mod;
		// 3:(0,3)
//		printf("[%d,%d]\n",f[i],g[i]);
	}
	printf("[%d]",f[n]); */
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	f[0]=g[0]=1;
	solve(0,n);
	printf("%d",f[n]);
}
