//题目有说时间回溯，回到过去追上自己，
//那么就联想到负环，有负环的图，
//才可以有时间的回溯，并且回溯的时间更长
//才能使得自己追上自己，符合题意
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int n,m,w;
struct point{
    int v;
    int w;
    point(int vv,int ww):v(vv),w(ww){}
};

vector<point> edge[505];
void addedge(int u,int v,int w){
    edge[u].push_back(point(v,w));
    return ;
}

int vis[505];//vis数组判断某个结点是否在队列里面
int cnt[505];//cnt数组存放各个结点进入队列的次数
int dis[505];//存放某个结点到起点的最短距离
void SPFA(int start){
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=500;i++) dis[i]=0x3f3f3f3f;
    queue<int> que;//注意这个和dijkstra不一样的
    while(!que.empty()) que.pop();
    que.push(start);
    vis[start]=1;
    dis[start]=0;
    cnt[start]=1;
    while(!que.empty()){
        int u=que.front();
        que.pop();
        vis[u]=0;
        for(int i=0;i<edge[u].size();i++){
            int v=edge[u][i].v;
            int w=edge[u][i].w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(vis[v]==0){
                    que.push(v);
                    vis[v]=1;
                    cnt[v]++;
                    //某点松弛次数超过n，那么就是有负环了
                    if(cnt[v]>n){
                        cout<<"YES"<<endl;
                        return ;
                    }
                }
            }
        }
    }
    cout<<"NO"<<endl;
    return ;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        for(int i=1;i<=500;i++){
            edge[i].clear();
        }
        cin>>n>>m>>w;
        for(int i=1;i<=m;i++){
            int x,y,z;
            cin>>x>>y>>z;
            addedge(x,y,z);
            addedge(y,x,z);
        }
        for(int i=1;i<=w;i++){
            int x,y,z;
            cin>>x>>y>>z;
            addedge(x,y,-z);
        }//题目要求这个负权路是单向的
        SPFA(1);
    }
    return 0;
}
