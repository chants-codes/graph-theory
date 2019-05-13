//这个模板可以解决简单的带重边的问题
//注意djikstra边权非负
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

int n,m;
int dis[1005];
int vis[1005];
struct point{
    int v;int w;
    point(int _v,int _w):v(_v),w(_w){}
};

vector<point> edge[1005];
//用vector+结构体 来存图
//类似邻接链表
void addedge(int u,int v,int w){
    edge[u].push_back(point(v,w));
}//加边函数

struct node{//给队列的结构体，不可以混用
    int v;int w;
    node(int _v=0,int _w=0):v(_v),w(_w){}
    bool operator <(const node &r)const{
        return w>r.w;
    }//比较函数，毕竟是优先队列
};

void dijkstra(int start){
    priority_queue<node> que;
    while(!que.empty()) que.pop();
    dis[start]=0;
    que.push(node(start,0));
    node tmp;
    while(!que.empty()){
        tmp=que.top();
        que.pop();
        if(vis[tmp.v]==1) continue;
        vis[tmp.v]=1;
        for(int i=0;i<edge[tmp.v].size();i++){//遍历这个点的所有终点
            int u=tmp.v;//起点u
            int v=edge[tmp.v][i].v;//终点v
            int w=edge[tmp.v][i].w;//边权w
            if(!vis[v]&&dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                que.push(node(v,dis[v]));
            }//注意这里push的边权是dis
        }
    }
    return ;
}

int main(){
    cin>>m;
    cin>>n;
    for(int i=0;i<=1003;i++)
        edge[i].clear();
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        addedge(x,y,z);
        addedge(y,x,z);
    }//无向图
    memset(dis,0x3f3f3f3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dijkstra(1);
    cout<<dis[n]<<endl;
}
