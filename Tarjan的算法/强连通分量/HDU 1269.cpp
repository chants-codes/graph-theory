#include<cstdio>
#include<algorithm>
#include<string.h>
using namespace std;

struct node{
    int v,next;
}edge[100005];

int DFN[100005],LOW[100005];
int stackk[100005],heads[100005],visit[100005];
int cnt,tot,indexx,ans;

void add(int x,int y){
    edge[++cnt].next=heads[x];
    edge[cnt].v = y;
    heads[x]=cnt;
    return ;
}

void tarjan(int x){
    DFN[x]=LOW[x]=++tot;
    stackk[++indexx]=x;
    visit[x]=1;//其实vis数组可以不要的，用dfn数组直接代替
    for(int i=heads[x]; i!=-1; i=edge[i].next){//注意这个邻接矩阵的for循环
        if(!DFN[edge[i].v]){
            tarjan(edge[i].v);
            LOW[x]=min(LOW[x],LOW[edge[i].v]);
        }
        else if(visit[edge[i].v ]){
            LOW[x]=min(LOW[x],DFN[edge[i].v]);
        }
    }
    if(LOW[x]==DFN[x]){
        while(x!=stackk[indexx+1]){
            //printf("%d ",stackk[indexx]);
            //上面那句是用来打印强连通分量的点的语句
            visit[stackk[indexx]]=0;
            indexx--;
        }
        ans++;
        //printf("\n");
        //"\n"和上方打印语句对应
    }
    return ;
}

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(n==0&&m==0) break;
        //注意这个初始化需要很多函数
        //还有就是我没清空那个结构体，清空了cnt应该就不需要清空结构体了
        cnt=0;
        ans=0;
        indexx=0;
        tot=0;
        memset(heads,-1,sizeof(heads));
        memset(visit,0,sizeof(visit));
        memset(DFN,0,sizeof(DFN));
        memset(LOW,0,sizeof(LOW));
        int x,y;
        for(int i=1; i<=m; i++){
            scanf("%d%d",&x,&y);
            add(x,y);
        }
        for(int i=1; i<=n; i++){
            if(!DFN[i]) tarjan(i);
        }
        if(ans==1) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
