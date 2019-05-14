//两次dijkstra
//题目是有向图，两点之间有多条边
//正向图，求出x到其他点的最短路径
//反向图，求出其他点到x的最短路径
//单目的最短路径=原图的反图求单源最短路径
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m,x;
int mapp[1005][1005];

struct point{
    int v;int w;
    point(int vv,int ww):v(vv),w(ww){}
    bool operator <(const point &r)const{
        return w>r.w;
    }
};

int dis[1005];
int vis[1005];
void dijkstra(int start){
    memset(dis,0x3f3f3f3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    priority_queue<point> que;
    while(!que.empty()) que.pop();
    que.push(point(start,0));
    dis[start]=0;
    while(!que.empty()){
        point tmp=que.top();
        que.pop();
        if(vis[tmp.v]==1) continue;
        vis[tmp.v]=1;
        for(int i=1;i<=n;i++){
            if(vis[i]==0&&dis[i]>dis[tmp.v]+mapp[tmp.v][i]){
                dis[i]=dis[tmp.v]+mapp[tmp.v][i];
                que.push(point(i,dis[i]));
            }
        }
    }
}

int ans[1005];

int main(){
    memset(ans,0,sizeof(ans));
    memset(mapp,0x3f3f3f3f,sizeof(mapp));
    cin>>n>>m>>x;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        mapp[a][b]=c;
    }
    dijkstra(x);
    for(int i=1;i<=n;i++){
        ans[i]+=dis[i];
        for(int j=i+1;j<=n;j++){
            int tmpp=mapp[i][j];
            mapp[i][j]=mapp[j][i];
            mapp[j][i]=tmpp;
        }//正向边转成反向边
    }
    dijkstra(x);//再求一次dijkstra
    int maxx=0;
    for(int i=1;i<=n;i++){
        ans[i]+=dis[i];
        maxx=max(maxx,ans[i]);
    }//输出最大值
    cout<<maxx<<endl;
    return 0;
}