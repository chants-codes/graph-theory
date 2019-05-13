//具体做法：
//1，把所有边存下来，然后做一次比较，让边权大的靠前
//2，遍历所有边，建立一棵树
//3，当点1和点n的father相同时，
//就说明这两点刚好连通，此时输出这个边权，结束
//这样写可以保证这棵树上面的边都是最大边，
//所以直接输出就可以
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;

int n,m;
int father[1005];

struct edge{
    int u;
    int v;
    int w;
}edgee[1005*500];
//开启结构体存下所有的边
//实测，这里用的空间其实不大

bool cmp(edge a,edge b){
    return a.w>b.w;
}//给sort使用的比较函数

int findroot(int x){
    while(father[x]!=-1) x=father[x];
    return x;
}//类似并查集，这个操作是寻找根结点

bool unionn(int x,int y){
    int fathx=findroot(x);
    int fathy=findroot(y);
    if(fathx==fathy) return false;
    father[fathx]=fathy;
    return true;
}//连接两个原本没有关联的点
//注意bool的妙用

int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    int casee=1;
    while(T--){
        cin>>n>>m;
        memset(father,-1,sizeof(father));
        for(int i=0;i<m;i++){
            int x,y,z;
            cin>>x>>y>>z;
            edgee[i].u=x;
            edgee[i].v=y;
            edgee[i].w=z;
        }//由于我们用的操作是并查集
        //所以不需要存两个边
        sort(edgee,edgee+m,cmp);
        int ans=0;
        for(int i=0;i<m;i++){
            if(unionn(edgee[i].u,edgee[i].v)){
                if(findroot(1)!=-1&&findroot(n)!=-1&&findroot(1)==findroot(n)){
                    ans=edgee[i].w;
                    break;
                }
            }
        }
        cout<<"Scenario #"<<casee++<<":"<<endl;
        cout<<ans<<endl<<endl;
    }
    return 0;
}
