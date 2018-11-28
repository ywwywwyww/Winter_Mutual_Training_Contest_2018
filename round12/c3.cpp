#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
int n,pn=0,fail[2333];
typedef vector<ld> vld;
vld ps[2333]; ld x[2333],delta[2333];
int main()
{
	freopen("c3.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf",x+i);
    int best=0;
    for(int i=1;i<=n;i++)
    {
        ld dt=-x[i];
        for(int j=0;j<ps[pn].size();j++)
            dt+=x[i-j-1]*ps[pn][j];
        delta[i]=dt;
        if(fabs(dt)<=1e-7) continue;
        fail[pn]=i; if(!pn) {ps[++pn].resize(i); continue;}
        vld&ls=ps[best]; ld k=-dt/delta[fail[best]];
        vld cur; cur.resize(i-fail[best]-1); //trailing 0
        cur.pb(-k); for(int j=0;j<ls.size();j++) cur.pb(ls[j]*k);
        if(cur.size()<ps[pn].size()) cur.resize(ps[pn].size());
        for(int j=0;j<ps[pn].size();j++) cur[j]+=ps[pn][j];
        if(i-fail[best]+(int)ps[best].size()>=ps[pn].size()) best=pn;
        ps[++pn]=cur;
    }
    for(unsigned g=0;g<ps[pn].size();g++)
        cout<<ps[pn][g]<<" "; puts("");
}
