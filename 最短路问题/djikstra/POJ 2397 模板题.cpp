//���ģ����Խ���򵥵Ĵ��رߵ�����
//ע��djikstra��Ȩ�Ǹ�
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
//��vector+�ṹ�� ����ͼ
//�����ڽ�����
void addedge(int u,int v,int w){
    edge[u].push_back(point(v,w));
}//�ӱߺ���

struct node{//�����еĽṹ�壬�����Ի���
    int v;int w;
    node(int _v=0,int _w=0):v(_v),w(_w){}
    bool operator <(const node &r)const{
        return w>r.w;
    }//�ȽϺ������Ͼ������ȶ���
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
        for(int i=0;i<edge[tmp.v].size();i++){//���������������յ�
            int u=tmp.v;//���u
            int v=edge[tmp.v][i].v;//�յ�v
            int w=edge[tmp.v][i].w;//��Ȩw
            if(!vis[v]&&dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                que.push(node(v,dis[v]));
            }//ע������push�ı�Ȩ��dis
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
    }//����ͼ
    memset(dis,0x3f3f3f3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dijkstra(1);
    cout<<dis[n]<<endl;
}
