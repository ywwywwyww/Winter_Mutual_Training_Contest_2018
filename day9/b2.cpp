#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
T i=0;char c;
while(!isdigit(c=getchar())&&c!='-');
bool neg=c=='-';
neg?c=getchar():0;
while(i=i*10-'0'+c,isdigit(c=getchar()));
return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
namespace G{
const int logN=16;
const int putptcnt=(logN*(::N*2)+2*logN*::N)*4;
const int N=::N*4+putptcnt,E=putptcnt*2+(logN*::N*2+2*::N*2)*4;
int to[E],bro[E],head[N],e=0,n=0;
bool val[E];
inline int nn(){
n++;
head[n]=-1;
return n;
}
inline void ae(int u,int v,int w){
to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
}
int dis[N],que[N<<1];
bool vis[N];
inline int bfs(int s,int t){
mset(dis+1,127,n);
mset(vis+1,0,n);
int qh=N,qt=N;
dis[s]=0,que[qt++]=s;
for(;qh<qt;){
const int x=que[qh++];
if(vis[x])continue;
if(x==t)return dis[t];
vis[x]=true;
for(int i=head[x],v;~i;i=bro[i]){
if(dis[v=to[i]]>dis[x]+val[i]){
dis[v]=dis[x]+val[i],que[val[i]?qt++:--qh]=v;
}
}
}
assert(false);
}
}
namespace seg{
const int N=::N*2*2;
struct Node;
typedef Node* node;
struct Node{
node lson,rson;
int l,m,r;
int pt;
bool clrtag;
inline void putclr(){
pt=0;
clrtag=true;
}
inline void dn(){
if(clrtag){
if(l<r){
lson->putclr();
rson->putclr();
}
clrtag=false;
}
}
inline void putpt(int x){
dn();
if(pt){
const int mpt=G::nn();
G::ae(mpt,x,0);
G::ae(mpt,pt,0);
pt=mpt;
}else{
pt=x;
}
}
inline void force_dn(){
assert(l<r);
dn();
if(pt){
lson->putpt(pt);
rson->putpt(pt);
pt=0;
}
}
}pool[N];
node n;
node build(int l,int r){
const node x=n++;
x->l=l,x->m=(l+r)>>1,x->r=r;
x->clrtag=true;
if(l!=r){
x->lson=build(l,x->m);
x->rson=build(x->m+1,r);
}
return x;
}
void setclr(node x,int l,int r){
if(x->clrtag)return;
if(x->l==l&&x->r==r)return x->putclr();
x->force_dn();
if(r<=x->m)return setclr(x->lson,l,r);
if(l>x->m)return setclr(x->rson,l,r);
setclr(x->lson,l,x->m);
setclr(x->rson,x->m+1,r);
}
void cov(node x,int l,int r,int pt){
x->dn();
if(x->l==l&&x->r==r)return x->putpt(pt);
if(r<=x->m)return cov(x->lson,l,r,pt);
if(l>x->m)return cov(x->rson,l,r,pt);
cov(x->lson,l,x->m,pt);
cov(x->rson,x->m+1,r,pt);
}
void askpt(node x,int p,int pt){
if(x->clrtag)return;
if(x->pt){
G::ae(pt,x->pt,1);
}
if(x->l<x->r){
askpt(p<=x->m?x->lson:x->rson,p,pt);
}
}
}
struct Rec{
int x1,x2,y1,y2;
int e[4];
}rec[N];
struct Event{
int x,l,r,tp,idx;
inline friend bool operator < (const Event &a,const Event &b){
return a.x!=b.x?a.x<b.x:a.tp>b.tp;
}
}ev[N<<1];
struct Intv{
int l,r;
inline friend bool operator < (const Intv &a,const Intv &b){
return a.l<b.l;
}
};
seg::node rt;
int wall;
inline void upd_node(map<int,int>&m,int a,int b){
map<int,int>::iterator it=m.find(a);
if(it==m.end()){
m[a]=b;
}else{
if(it->second==wall){
G::ae(wall,b,1);
G::ae(b,wall,1);
}else{
G::ae(b,it->second,0);
}
it->second=b;
}
}
inline void work_edge(int n){
//rec[0]==boundary
//rec[1]==start
//rec[2]==end
//rec[3,n]==rectangle
typedef map<int,int>mii;
mii hori;
set<Intv>s;
rt->putclr();
wall=rec[0].e[2];
seg::cov(rt,0,rec[0].y2,wall);
s.insert((Intv){0,rec[0].y2});
for(int i=rec[0].y1;i<=rec[0].y2;i++){
hori[i]=wall;
}
int es=0;
for(int i=1;i<=n;i++){
ev[++es]=(Event){rec[i].x1,rec[i].y1,rec[i].y2,1,i};
ev[++es]=(Event){rec[i].x2,rec[i].y1,rec[i].y2,-1,i};
}
sort(ev+1,ev+es+1);
for(int i=1;i<=es;i++){
const int j=ev[i].idx;
if(ev[i].tp==1){
//split block
set<Intv>::iterator it=--s.upper_bound((Intv){ev[i].l,0});
const Intv v1=(Intv){it->l,ev[i].l};
const Intv v2=(Intv){ev[i].r,it->r};
assert(v1.l<v1.r);
assert(v2.l<v2.r);
s.erase(it),s.insert(v1),s.insert(v2);
//change covering
seg::cov(rt,v1.l,v2.r,rec[j].e[2]);
//block all
if(ev[i].r-ev[i].l>1){
seg::setclr(rt,ev[i].l+1,ev[i].r-1);
}
for(mii::iterator it=hori.upper_bound(ev[i].l);it->first<ev[i].r;hori.erase(it++));
}else{
//add edge hor->ver
seg::askpt(rt,ev[i].l,rec[j].e[3]);
seg::askpt(rt,ev[i].r,rec[j].e[1]);
//add edge hor->hor
upd_node(hori,ev[i].l,rec[j].e[3]);
upd_node(hori,ev[i].r,rec[j].e[1]);
//merge block
set<Intv>::iterator it=s.lower_bound((Intv){ev[i].r,0});
const Intv v2=*it,v1=*--it;
assert(v1.r==ev[i].l);
assert(v2.l==ev[i].r);
s.erase(it++),s.erase(it),s.insert((Intv){v1.l,v2.r});
//change covering
seg::cov(rt,v1.l,v2.r,rec[j].e[0]);
}
}
}
namespace disc{
const int N=::N<<1;
int *num[N],n;
inline void init(){
n=0;
}
inline void psh(int &x){
num[++n]=&x;
}
inline bool ncmp(int* a,int* b){
return *a<*b;
}
inline int main(){
sort(num+1,num+n+1,ncmp);
int m=0;
for(int i=1,&j=m,v=-1;i<=n;i++){
*num[i]=v<*num[i]?v=*num[i],++j:j;
}
return m;
}
}
int main(){
freopen("b.in","r",stdin);
freopen("b2.out","w",stdout);
rec[1].x1=rec[1].x2=ni,rec[1].y1=rec[1].y2=ni;
rec[2].x1=rec[2].x2=ni,rec[2].y1=rec[2].y2=ni;
for(int i=0,x1=G::nn(),x2=G::nn();i<4;i++){
rec[0].e[i]=G::nn();
rec[1].e[i]=x1;
rec[2].e[i]=x2;
}
for(int i=0;i<4;i++){
G::ae(rec[0].e[i],rec[0].e[(i+1)&3],1);
G::ae(rec[0].e[i],rec[0].e[(i+3)&3],1);
}
const int n=ni+2;
for(int i=3;i<=n;i++){
rec[i]=(Rec){ni,ni,ni,ni,G::nn(),G::nn(),G::nn(),G::nn()};
}
disc::init();
for(int i=1;i<=n;i++){
disc::psh(rec[i].x1);
disc::psh(rec[i].x2);
}
rec[0].x1=0,rec[0].x2=disc::main()+1;
disc::init();
for(int i=1;i<=n;i++){
disc::psh(rec[i].y1);
disc::psh(rec[i].y2);
}
rec[0].y1=0,rec[0].y2=disc::main()+1;
{//add edge
seg::n=seg::pool,rt=seg::build(0,rec[0].y2);
work_edge(n);
for(int i=0,mx=rec[0].x2;i<=n;i++){
rec[i].x1=mx-rec[i].x1;
rec[i].x2=mx-rec[i].x2;
swap(rec[i].x1,rec[i].x2);
swap(rec[i].e[0],rec[i].e[2]);
}
work_edge(n);
for(int i=0;i<=n;i++){
swap(rec[i].x1,rec[i].y1);
swap(rec[i].x2,rec[i].y2);
swap(rec[i].e[0],rec[i].e[1]);
swap(rec[i].e[2],rec[i].e[3]);
}
seg::n=seg::pool,rt=seg::build(0,rec[0].y2);
work_edge(n);
for(int i=0,mx=rec[0].x2;i<=n;i++){
rec[i].x1=mx-rec[i].x1;
rec[i].x2=mx-rec[i].x2;
swap(rec[i].x1,rec[i].x2);
swap(rec[i].e[0],rec[i].e[2]);
}
work_edge(n);
}
printf("%d\n",G::bfs(rec[1].e[0],rec[2].e[0])+1);
return 0;
}
