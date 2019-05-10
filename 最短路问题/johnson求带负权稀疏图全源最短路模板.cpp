/*一开始我想
这个Johnson是求稀疏图的算法，
那么就用邻接链表存图好了；
但是后来才发现，
要去求全源的最短路，
还是开邻接矩阵好*/
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXX 1005
#define INF 0x3f3f3f3f

int BF_check;
int n,m;
int dis[MAXX][MAXX];//存图

int h[MAXX];//h函数，同时也是s点到各个点的最短路
void BF(int s){//用BF不用SPFA是因为BF求负环更方便更快
    memset(h,0,sizeof(h));//起始全部为0
    for(int i=1;i<=n;i++){
        //共n-1次松弛
        if(i==n){
            BF_check=0;
            return ;
        }//如果松弛次数大于n-1，那么就是有负环
        int check=0;
        for(int k=1;k<=n;k++){
            for(int j=1;j<=n;j++){//注意下面代码的写法
                if(h[k]>h[j]+dis[j][k]){
                    h[k]=h[j]+dis[j][k];
                    check=1;
                }//这里的check可以判断是否进行松弛
            }
        }
        if(!check) break;
    }//如果没有松弛，说明BF结束
    for(int i=1;i<=n;i++)
        cout<<"h["<<i<<"]= "<<h[i]<<endl;
    //输出h函数的值
    cout<<endl;
    return ;
}

struct point{
    int num;//点的编号
    int val;//此点到起始点的距离
    point(int _num=0,int _val=0):num(_num),val(_val){}
    bool operator <(const point &r)const{
        return val>r.val;
    }//做自定义比较函数
};//开结构体,结构体没有名称的话不可以放在函数里面

int ans[MAXX][MAXX];
void dijkstra(int start){
    int vis[MAXX];
    memset(vis,0,sizeof(vis));
    priority_queue<point> que;
    while(!que.empty()) que.pop();
    ans[start][start]=0;
    que.push(point(start,0));
    while(!que.empty()){
        point tmp=que.top();
        que.pop();
        if(vis[tmp.num]) continue;
        vis[tmp.num]=1;//走过就不走，没走过就进循环
        for(int i=1;i<=n;i++){
            if(dis[tmp.num][i]==INF) continue;//如果这两个点没有连接，跳过
            if(vis[i]==1) continue;//如果曾经走过，跳过
            if(ans[start][i]>ans[start][tmp.num]+dis[tmp.num][i]){
                ans[start][i]=ans[start][tmp.num]+dis[tmp.num][i];
                que.push(point(i,ans[start][i]));//这里写错了wa好久
            }//有一个点没有走过且其到起点的距离可以变得更小，那么就更新入队
        }
    }
    return ;
}//注意更新的最短边可以被记忆化利用

int main(){
    memset(dis,INF,sizeof(dis));
    memset(ans,INF,sizeof(ans));
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        dis[x][y]=z;
    }//题目所给的有向边和权值
    for(int i=1;i<=n;i++){
        dis[i][i]=0;
        dis[n+1][i]=0;
    }//自环和新增的s点初始化
    BF_check=1;
    BF(n+1);
    if(!BF_check){
        cout<<endl<<"the input graph contains a negative-weight cycle"<<endl;
        return 0;
    }//有负环，那就结束算法
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dis[i][j]!=INF&&i!=j){
                dis[i][j]=dis[i][j]+h[i]-h[j];
                cout<<"从"<<i<<"点到"<<j<<"点的边更新后的权值是: "<<dis[i][j]<<endl;
            }
        }//更改边的权值：现在=之前+起点h函数-终点h函数
    }//到时候需要改回来
    for(int i=1;i<=n;i++){
        dijkstra(i);
    }//每个点做迪杰斯特拉,求最短路
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(ans[i][j]==INF) continue;
            ans[i][j]=ans[i][j]-h[i]+h[j];
        }//现在=之前+终点h函数-起点h函数
    }//重新把权值改回来
    //下方代码是输出,为了直观所以输出比较多
    cout<<endl<<"最终结果为:"<<endl<<"  ";
    for(int i=1;i<=n;i++){
        cout<<" "<<i<<" ";
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        cout<<i<<" ";
        for(int j=1;j<=n;j++){
            if(ans[i][j]<INF&&ans[i][j]>=0) cout<<" "<<ans[i][j]<<" ";
            if(ans[i][j]<0) cout<<ans[i][j]<<" ";
            if(ans[i][j]==INF) cout<<"INF";
        }
        cout<<endl;
    }
    return 0;
}
/*
5 6
2 1 4
2 3 2
2 4 1
3 1 -1
4 5 2
5 2 -1
*/
