#include <bits/stdc++.h>
#define MAXN 10000
using namespace std;

int n,m;
int pos[MAXN][4];

const int N=10;

bool check(int x,int y){
if(pos[x][1]>=pos[y][0] && pos[y][1]>=pos[x][0] && pos[x][3]>=pos[y][2] && pos[y][3]>=pos[x][2]) return 1;
return 0;
}

int main(){
freopen("b.in","w",stdout);
srand(time(0));
for(int i=1;i<=10000;i++)
	rand();
pos[1][0]=pos[1][1]=rand()%3;
pos[1][2]=pos[1][3]=rand()%3;
pos[2][0]=pos[2][1]=N-rand()%3;
pos[2][2]=pos[2][3]=N-rand()%3;
n=2;
for(int i=1;i<=100000;i++){
int x1=rand()%N,y1=rand()%N;
int x2=x1+rand()%5+1,y2=y1+rand()%5+1;
n++;
pos[n][0]=x1;
pos[n][1]=x2;
pos[n][2]=y1;
pos[n][3]=y2;
bool flag=0;
for(int j=1;j<n;j++)
if(check(j,n)){
flag=1;
break;
}
if(flag) n--;
}
printf("%d %d %d %d\n",pos[1][0],pos[1][2],pos[2][0],pos[2][2]);
printf("%d\n",n-2);
for(int i=3;i<=n;i++) 
printf("%d %d %d %d\n",pos[i][0],pos[i][1],pos[i][2],pos[i][3]);
return 0;
}
