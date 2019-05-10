/*һ��ʼ����
���Johnson����ϡ��ͼ���㷨��
��ô�����ڽ������ͼ���ˣ�
���Ǻ����ŷ��֣�
Ҫȥ��ȫԴ�����·��
���ǿ��ڽӾ����*/
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXX 1005
#define INF 0x3f3f3f3f

int BF_check;
int n,m;
int dis[MAXX][MAXX];//��ͼ

int h[MAXX];//h������ͬʱҲ��s�㵽����������·
void BF(int s){//��BF����SPFA����ΪBF�󸺻����������
    memset(h,0,sizeof(h));//��ʼȫ��Ϊ0
    for(int i=1;i<=n;i++){
        //��n-1���ɳ�
        if(i==n){
            BF_check=0;
            return ;
        }//����ɳڴ�������n-1����ô�����и���
        int check=0;
        for(int k=1;k<=n;k++){
            for(int j=1;j<=n;j++){//ע����������д��
                if(h[k]>h[j]+dis[j][k]){
                    h[k]=h[j]+dis[j][k];
                    check=1;
                }//�����check�����ж��Ƿ�����ɳ�
            }
        }
        if(!check) break;
    }//���û���ɳڣ�˵��BF����
    for(int i=1;i<=n;i++)
        cout<<"h["<<i<<"]= "<<h[i]<<endl;
    //���h������ֵ
    cout<<endl;
    return ;
}

struct point{
    int num;//��ı��
    int val;//�˵㵽��ʼ��ľ���
    point(int _num=0,int _val=0):num(_num),val(_val){}
    bool operator <(const point &r)const{
        return val>r.val;
    }//���Զ���ȽϺ���
};//���ṹ��,�ṹ��û�����ƵĻ������Է��ں�������

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
        vis[tmp.num]=1;//�߹��Ͳ��ߣ�û�߹��ͽ�ѭ��
        for(int i=1;i<=n;i++){
            if(dis[tmp.num][i]==INF) continue;//�����������û�����ӣ�����
            if(vis[i]==1) continue;//��������߹�������
            if(ans[start][i]>ans[start][tmp.num]+dis[tmp.num][i]){
                ans[start][i]=ans[start][tmp.num]+dis[tmp.num][i];
                que.push(point(i,ans[start][i]));//����д����wa�þ�
            }//��һ����û���߹����䵽���ľ�����Ա�ø�С����ô�͸������
        }
    }
    return ;
}//ע����µ���̱߿��Ա����仯����

int main(){
    memset(dis,INF,sizeof(dis));
    memset(ans,INF,sizeof(ans));
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        dis[x][y]=z;
    }//��Ŀ����������ߺ�Ȩֵ
    for(int i=1;i<=n;i++){
        dis[i][i]=0;
        dis[n+1][i]=0;
    }//�Ի���������s���ʼ��
    BF_check=1;
    BF(n+1);
    if(!BF_check){
        cout<<endl<<"the input graph contains a negative-weight cycle"<<endl;
        return 0;
    }//�и������Ǿͽ����㷨
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dis[i][j]!=INF&&i!=j){
                dis[i][j]=dis[i][j]+h[i]-h[j];
                cout<<"��"<<i<<"�㵽"<<j<<"��ı߸��º��Ȩֵ��: "<<dis[i][j]<<endl;
            }
        }//���ıߵ�Ȩֵ������=֮ǰ+���h����-�յ�h����
    }//��ʱ����Ҫ�Ļ���
    for(int i=1;i<=n;i++){
        dijkstra(i);
    }//ÿ�������Ͻ�˹����,�����·
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(ans[i][j]==INF) continue;
            ans[i][j]=ans[i][j]-h[i]+h[j];
        }//����=֮ǰ+�յ�h����-���h����
    }//���°�Ȩֵ�Ļ���
    //�·����������,Ϊ��ֱ����������Ƚ϶�
    cout<<endl<<"���ս��Ϊ:"<<endl<<"  ";
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
