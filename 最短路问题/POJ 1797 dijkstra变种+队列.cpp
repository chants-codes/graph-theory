#include<algorithm>
#include<queue>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<math.h>
using namespace std;

const int maxn=1005;
const int oo=0xfffffff;

struct node{
    int y,weight;
    node(int y,int weight):y(y),weight(weight){}
};

vector<node> G[maxn];
int v[maxn];
//v数组存放起点到下标点所在路径的最短边

void spfa(int s){
    queue<int> Q;
    Q.push(s);
    while(Q.size()){
        s=Q.front();
        Q.pop();
        int len=G[s].size();
        for(int i=0;i<len;i++){
            node q=G[s][i];
            if(v[s]>v[q.y]&&q.weight>v[q.y]){
            //起点到s的最短边要比到s的邻接点的最短边要大
            //且s到该邻接点的权值要比起点到该点的最短边大
                v[q.y]=min(v[s],q.weight);
                Q.push(q.y);
            }
        }
    }
}

int main(){
    int T,t=1;
    scanf("%d",&T);
    while(T--){
        int N,M,a,b,w,i;
        scanf("%d%d",&N,&M);
        for(i=1;i<=N;i++){
            G[i].clear();
            v[i]=-oo;
        }//注意这里的初始化，很讲究
        v[1]=oo;
        for(i=0;i<M;i++){
            scanf("%d%d%d",&a,&b,&w);
            G[a].push_back(node(b,w));
            G[b].push_back(node(a,w));
        }
        spfa(1);
        printf("Scenario #%d:\n",t++);
        for(int i=1;i<=N;i++)
            printf("%d ",v[i]);
        printf("\n");
    }
    return 0;
}
