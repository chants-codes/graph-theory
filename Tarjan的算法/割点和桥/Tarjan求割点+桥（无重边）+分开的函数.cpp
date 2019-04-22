#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=10000+10;
int index;
int  dfn[maxn];
int low[maxn];
int Father[maxn];//dfs树，存放父亲结点

set<int> point;//存放割点
vector<int> G[maxn];//存放题目所给的边集
typedef pair<int,int> Edge;
vector<Edge> bridge;//存放桥

void Tarjan(int u,int father){
    dfn[u]=low[u]=++index;
    Father[u]=father;//记录该点从哪条边过来
    for(int i=0; i<G[u].size(); i++){
        int v=G[u][i];
        if(!dfn[v]){//没去过
            Tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(father!=v)//只能由非父子边更新
            low[u]=min(low[u],dfn[v]);
    }
}

int Count(int n){
    int nson=0;//根节点的子树
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i,0);
    //必须要求结点编号从1开始，不能从别的数开始，比如0
    for(int v=2; v<=n; v++){//1为根
        int u=Father[v];
        if(u==1) nson++;
        else if(dfn[u]<=low[v]) point.insert(u);
    }//v到不了u之前的点
    if(nson>1) point.insert(1);
    //上面求割点，下面求桥
    for(int u=1; u<=n; u++){
        int v=Father[u];
        if(v>0&&dfn[v]<low[u]) bridge.push_back(Edge(v,u));
    }//注意这个求桥代码是无法判断重边的，有重边会输出重边
}

int main(){
    int n,m;
    cin>>n>>m;
    while(m--){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    index=0;
    memset(dfn,0,sizeof(0));
    Count(n);
    set<int>::iterator it;
    for(it=point.begin();it!=point.end();it++){
        if(it==point.begin()) cout<<*it;
        else cout<<" "<<*it;
    }//输出割点，注意set会排序，可以选择用queue来去重且有原序
    cout<<endl;
    for(int i=0; i<bridge.size(); i++)
        cout<<bridge[i].first<<','<<bridge[i].second<<endl;
    //输出桥，注意这个代码有重边会错！！！！！
    return 0;
}
