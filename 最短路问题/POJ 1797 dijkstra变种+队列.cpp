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
//v��������㵽�±������·������̱�

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
            //��㵽s����̱�Ҫ�ȵ�s���ڽӵ����̱�Ҫ��
            //��s�����ڽӵ��ȨֵҪ����㵽�õ����̱ߴ�
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
        }//ע������ĳ�ʼ�����ܽ���
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
