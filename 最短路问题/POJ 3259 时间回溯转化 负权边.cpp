//��Ŀ��˵ʱ����ݣ��ص���ȥ׷���Լ���
//��ô�����뵽�������и�����ͼ��
//�ſ�����ʱ��Ļ��ݣ����һ��ݵ�ʱ�����
//����ʹ���Լ�׷���Լ�����������
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

int vis[505];//vis�����ж�ĳ������Ƿ��ڶ�������
int cnt[505];//cnt�����Ÿ�����������еĴ���
int dis[505];//���ĳ����㵽������̾���
void SPFA(int start){
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=500;i++) dis[i]=0x3f3f3f3f;
    queue<int> que;//ע�������dijkstra��һ����
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
                    //ĳ���ɳڴ�������n����ô�����и�����
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
        }//��ĿҪ�������Ȩ·�ǵ����
        SPFA(1);
    }
    return 0;
}
