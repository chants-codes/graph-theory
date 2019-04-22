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
int Father[maxn];//dfs������Ÿ��׽��

set<int> point;//��Ÿ��
vector<int> G[maxn];//�����Ŀ�����ı߼�
typedef pair<int,int> Edge;
vector<Edge> bridge;//�����

void Tarjan(int u,int father){
    dfn[u]=low[u]=++index;
    Father[u]=father;//��¼�õ�������߹���
    for(int i=0; i<G[u].size(); i++){
        int v=G[u][i];
        if(!dfn[v]){//ûȥ��
            Tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(father!=v)//ֻ���ɷǸ��ӱ߸���
            low[u]=min(low[u],dfn[v]);
    }
}

int Count(int n){
    int nson=0;//���ڵ������
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i,0);
    //����Ҫ�����Ŵ�1��ʼ�����ܴӱ������ʼ������0
    for(int v=2; v<=n; v++){//1Ϊ��
        int u=Father[v];
        if(u==1) nson++;
        else if(dfn[u]<=low[v]) point.insert(u);
    }//v������u֮ǰ�ĵ�
    if(nson>1) point.insert(1);
    //�������㣬��������
    for(int u=1; u<=n; u++){
        int v=Father[u];
        if(v>0&&dfn[v]<low[u]) bridge.push_back(Edge(v,u));
    }//ע��������Ŵ������޷��ж��رߵģ����ر߻�����ر�
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
    }//�����㣬ע��set�����򣬿���ѡ����queue��ȥ������ԭ��
    cout<<endl;
    for(int i=0; i<bridge.size(); i++)
        cout<<bridge[i].first<<','<<bridge[i].second<<endl;
    //����ţ�ע������������ر߻����������
    return 0;
}
