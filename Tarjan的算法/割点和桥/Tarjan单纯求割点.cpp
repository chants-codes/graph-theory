#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<set>

const int maxn = 2e4+5;
using namespace std;

vector <int> G[maxn];//邻接矩阵存图
int LOW[maxn];
int DFN[maxn];
set<int> ans;//查找割点过程中可能出现重复
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
        }//上一行，不是根节点且分离根部和子树那么就是割点
        LOW[u]=min(LOW[u],DFN[v]);//更新
        if(child>=2&&u==rt) ans.insert(u);
    }//上一行，是根节点且有一个以上的子树
}

int main(){
    int n,m;
    cin>>n>>m;//读入点数和边数
    int x,y;
    for(int i=1;i<=m;i++){
        cin>>x>>y;//读入两个连接的点
        G[x].push_back(y);
        G[y].push_back(x);//无向图
    }
    timing=0;
    ans.clear();
    memset(DFN,0,sizeof(DFN));
    memset(LOW,0,sizeof(LOW));//初始化
    for(int i=1;i<=n;i++)
        if(!DFN[i]) tarjan(i,i);
    cout<<ans.size()<<endl;
    set<int>::iterator it;
    for(it=ans.begin();it!=ans.end();it++){
        if(it==ans.begin()) cout<<*it;
        else cout<<" "<<*it;
    }//输出割点，注意用set排过序，可以选择用queue来去重且有序
    cout<<endl;
    return 0;
}
