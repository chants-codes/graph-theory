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
    visit[x]=1;//��ʵvis������Բ�Ҫ�ģ���dfn����ֱ�Ӵ���
    for(int i=heads[x]; i!=-1; i=edge[i].next){//ע������ڽӾ����forѭ��
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
            //�����Ǿ���������ӡǿ��ͨ�����ĵ�����
            visit[stackk[indexx]]=0;
            indexx--;
        }
        ans++;
        //printf("\n");
        //"\n"���Ϸ���ӡ����Ӧ
    }
    return ;
}

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(n==0&&m==0) break;
        //ע�������ʼ����Ҫ�ܶຯ��
        //���о�����û����Ǹ��ṹ�壬�����cntӦ�þͲ���Ҫ��սṹ����
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
