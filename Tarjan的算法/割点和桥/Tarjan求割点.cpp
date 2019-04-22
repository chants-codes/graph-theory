#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<set>

const int maxn = 2e4+5;
using namespace std;

vector <int> G[maxn];//�ڽӾ����ͼ
int LOW[maxn];
int DFN[maxn];
set<int> ans;//���Ҹ������п��ܳ����ظ�
int timing;

void tarjan(int u,int rt){
    LOW[u]=DFN[u]=++timing;
    int child=0;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(DFN[v]==0){
            child++;
            tarjan(v,rt);
            LOW[u]=min(LOW[u],LOW[v]);
            if(u!=rt&&LOW[v]>=DFN[u]) ans.insert(u);
        }//��һ�У����Ǹ��ڵ��ҷ��������������ô���Ǹ��
        LOW[u]=min(LOW[u],DFN[v]);//����
        if(child>=2&&u==rt) ans.insert(u);
    }//��һ�У��Ǹ��ڵ�����һ�����ϵ�����
}

int main(){
    int n,m;
    cin>>n>>m;//��������ͱ���
    int x,y;
    for(int i=1;i<=m;i++){
        cin>>x>>y;//�����������ӵĵ�
        G[x].push_back(y);
        G[y].push_back(x);//����ͼ
    }
    timing=0;
    ans.clear();
    memset(DFN,0,sizeof(DFN));
    memset(LOW,0,sizeof(LOW));//��ʼ��
    for(int i=1;i<=n;i++)
        if(!DFN[i]) tarjan(i,i);
    cout<<ans.size()<<endl;
    set<int>::iterator it;
    for(it=ans.begin();it!=ans.end();it++){
        if(it==ans.begin()) cout<<*it;
        else cout<<" "<<*it;
    }//�����㣬ע����set�Ź��򣬿���ѡ����queue��ȥ��������
    cout<<endl;
    return 0;
}
