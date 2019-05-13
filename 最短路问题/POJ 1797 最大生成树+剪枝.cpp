#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <queue>
#include <ctime>
#include <cmath>
#include <set>
#include <map>
using namespace std;
#define rep(i,j,k) for(int i = (int)(j);i <= (int)(k);i ++)
#define per(i,j,k) for(int i = (int)(j);i >= (int)(k);i --)
#define mmm(a,b)   memset(a,b,sizeof(a))
#define sz(x) ((int)(x).size())
#define pb push_back

typedef long long ll;
const int INF  = (int)0x3f3f3f3f;
const int MAXN = (int)1e3+7;
int N,M;

struct Node{
    int x,y,c;
    Node(int x = 0,int y = 0,int c = 0):x(x),y(y),c(c){}
}G[MAXN*MAXN];

bool cmp(const Node& a,const Node& b){
    return a.c > b.c;
}

int fa[MAXN];

int find1(int x){
    if (x != fa[x])fa[x] = find1(fa[x]);
    return fa[x];
}

bool Same(int x,int y){
    return find1(x) == find1(y);
}

void Union(int x,int y){
    int u = find1(x),v = find1(y);
    if (u == v)return ;
    fa[u] = v;
}

int Kruskal(){
    int res = INF;
    sort(G+1,G+1+M,cmp);
    rep(i,1,M){
        if (!Same(G[i].x,G[i].y)){
            Union(G[i].x,G[i].y);
            res = min(res,G[i].c);
        }
        if (Same(1,N))break;
    }
    return res;
}

void init(){
    rep(i,0,N)fa[i] = i;
}

int main()
{
    int T;
    scanf("%d",&T);
    rep(ca,1,T){
        scanf("%d %d",&N,&M);
        init();
        rep(i,1,M){
            scanf("%d %d %d",&G[i].x,&G[i].y,&G[i].c);
        }
        printf("Scenario #%d:\n%d\n\n",ca,Kruskal());
    }
}