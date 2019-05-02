//POJ 2186
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<cstdlib>

using namespace std;

#define M 50002
#define N 10002

stack<int>st;
int head[N],id[N],low[N],dfn[N],in[N],out[N];
int scnt,cnt,n,m,n2;
//cnt记录访问的次序

struct node{
    int to;//表示边的终点
    int next;//表示下一条边的下标位置
    int id;//这题好像没用到这个......
}edge[M];//边集

void addEdge(int u,int v,int k){
    edge[k].to=v;//表示这条边的终点
    edge[k].next=head[u];//表示同一起点的下一条边的下标位置
    head[u]=k;//更新下标位置，不明白的话建议手动模拟这个过程
}//邻接前向星存图

void Tarjan(int u){
    int k,v,t;
    dfn[u]=low[u]=cnt++;
    st.push(u);
    for(k=head[u];k!=-1;k=edge[k].next){
        v=edge[k].to;
        if(dfn[v]==-1) Tarjan(v);
        dfn[u]=min(dfn[u],low[v]);//更新
    }
    if(dfn[u]<low[u]){//判断一个点是否已经在一个强连通分量里面
        low[u]=dfn[u];//如果在，就更改一下low值
        return;
    }//如果不在，就是另一个强连通分量，那么就去do while里面
    do{//do while 语句先执行一遍内部，再判断
        id[t=st.top()]=scnt;//scnt是缩点的编号，id[t]表示t这个点所属的缩点编号
        low[t]=n;//表示这个点已经在这个强连通分量里面了
        out[scnt]++;//记录缩点内部点的总个数
        st.pop();
    }while(t!=u);
    scnt++;
}

int main(){
    int i,j,u,v,ans,flag;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(head,-1,sizeof(head));
        memset(dfn,-1,sizeof(dfn));
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        scnt=cnt=ans=0;
        for(i=0;i<m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u-1,v-1,i);
            //原作者的写法是这样的，
            //其实把所有for里面的0改成1也可以，
            //但是会很麻烦所以我没改
        }
        for(i=0;i<n;i++) if(dfn[i]==-1) Tarjan(i);
        //现在，id[]里面有所有点所属的缩点编号
        //out[]里面有每个缩点内部的点的总数
        for(i=0;i<n;i++){
            for(j=head[i];j!=-1;j=edge[j].next){
                int a=id[i],b=id[edge[j].to];
                if(a!=b) in[id[i]]++;
            }
        }//上面的代码记录了每个缩点的出度，根据缩点编号存放在in[]里面
        for(i=0;i<scnt;i++){
            if(!in[i]){
                ans++;
                flag=i;
            }
        }//记录出度为零的缩点，只有出度为零的缩点才可能是被所有奶牛崇拜的牛群
        //如果这样的牛群只有一群，那么就输出牛群个数
        //不然的话就是有多个牛群被不同部分奶牛崇拜，那么答案为零
        if(ans==1) printf("%d\n",out[flag]);
        else printf("0\n");
    }
    return 0;
}