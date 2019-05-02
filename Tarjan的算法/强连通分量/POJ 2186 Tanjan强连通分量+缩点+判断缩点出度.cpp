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
//cnt��¼���ʵĴ���

struct node{
    int to;//��ʾ�ߵ��յ�
    int next;//��ʾ��һ���ߵ��±�λ��
    int id;//�������û�õ����......
}edge[M];//�߼�

void addEdge(int u,int v,int k){
    edge[k].to=v;//��ʾ�����ߵ��յ�
    edge[k].next=head[u];//��ʾͬһ������һ���ߵ��±�λ��
    head[u]=k;//�����±�λ�ã������׵Ļ������ֶ�ģ���������
}//�ڽ�ǰ���Ǵ�ͼ

void Tarjan(int u){
    int k,v,t;
    dfn[u]=low[u]=cnt++;
    st.push(u);
    for(k=head[u];k!=-1;k=edge[k].next){
        v=edge[k].to;
        if(dfn[v]==-1) Tarjan(v);
        dfn[u]=min(dfn[u],low[v]);//����
    }
    if(dfn[u]<low[u]){//�ж�һ�����Ƿ��Ѿ���һ��ǿ��ͨ��������
        low[u]=dfn[u];//����ڣ��͸���һ��lowֵ
        return;
    }//������ڣ�������һ��ǿ��ͨ��������ô��ȥdo while����
    do{//do while �����ִ��һ���ڲ������ж�
        id[t=st.top()]=scnt;//scnt������ı�ţ�id[t]��ʾt�����������������
        low[t]=n;//��ʾ������Ѿ������ǿ��ͨ����������
        out[scnt]++;//��¼�����ڲ�����ܸ���
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
            //ԭ���ߵ�д���������ģ�
            //��ʵ������for�����0�ĳ�1Ҳ���ԣ�
            //���ǻ���鷳������û��
        }
        for(i=0;i<n;i++) if(dfn[i]==-1) Tarjan(i);
        //���ڣ�id[]���������е�������������
        //out[]������ÿ�������ڲ��ĵ������
        for(i=0;i<n;i++){
            for(j=head[i];j!=-1;j=edge[j].next){
                int a=id[i],b=id[edge[j].to];
                if(a!=b) in[id[i]]++;
            }
        }//����Ĵ����¼��ÿ������ĳ��ȣ����������Ŵ����in[]����
        for(i=0;i<scnt;i++){
            if(!in[i]){
                ans++;
                flag=i;
            }
        }//��¼����Ϊ������㣬ֻ�г���Ϊ�������ſ����Ǳ�������ţ��ݵ�ţȺ
        //���������ţȺֻ��һȺ����ô�����ţȺ����
        //��Ȼ�Ļ������ж��ţȺ����ͬ������ţ��ݣ���ô��Ϊ��
        if(ans==1) printf("%d\n",out[flag]);
        else printf("0\n");
    }
    return 0;
}