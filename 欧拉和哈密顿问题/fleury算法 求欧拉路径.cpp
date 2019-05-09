//fleury algorithm
#include<cstring>
#include<iostream>
using namespace std;

int stk[1005];
//开栈，栈的数目应该和边的数目一样，这里错了。
int top;
int N,M;
int mp[1005][1005];

void dfs(int x){
    stk[top]=x;
    top++;//入栈之后让栈顶加一
    for(int i=1;i<=N;i++){
        if(mp[x][i]){
            mp[x][i]=mp[i][x]=0;//删除此边
            dfs(i);
            break;
        }
    }
}

void fleury(int ss){
    top=0;
    stk[top]=ss;//将起点放入Euler路径中
    top++;//入栈之后让栈顶加一，现在top指向空
    while(top>0){//while(!sta.empty())
        int brige=1;//标记是否为桥
        for(int i=1;i<=N;i++){//试图搜索一条边不是割边(桥)
            if(mp[stk[top-1]][i]){//注意入栈操作，top-1指向栈顶，top指向空
                brige=0;
                break;
            }
        }
        top--;//注意入栈时候的操作，这里减一还可以帮助输出。
        if (brige) cout<<stk[top]<<" ";
        //注意这里输出的欧拉回路是反了的，先输出终点
        //如果没有点可以扩展，输出并出栈
        else dfs(stk[top]);//否则继续搜索欧拉路径
    }
    cout<<endl;
}

int main(){
    while(cin>>N>>M){
        memset(mp,0,sizeof(mp));
        for(int i=0;i<M;i++){
            int x,y;
            cin>>x>>y;
            mp[x][y]=mp[y][x]=1;
        }
        int num=0;
        int ss=1;//初始化起点，注意这里一定要初始化
        //如果图里面全部都是度为偶数的点，那么就要先前设定一个起点
        for(int i=1;i<=N;i++){
            int deg=0;
            for(int j=1;j<=N;j++){
                deg+=mp[i][j];
            }
            if(deg%2==1){
                ss=i;//有奇数度点的话就更新ss
                num++;
                cout<<i<<endl;//输出度为奇数的点
            }
        }//上方代码处理的是度的问题
        if(num==0||num==2) fleury(ss);
        else cout<<"No Euler path"<<endl;
    }
    return 0;
}

/*
9 12
1 5
1 9
5 3
5 4
5 8
2 3
2 4
4 6
6 7
6 8
7 8
8 9
start:6
end:4
path:4 5 8 7 6 8 9 1 5 3 2 4 6

6 7
1 2
2 3
1 3
3 4
4 5
4 6
5 6
start:4
end:3
path:3 2 1 3 4 6 5 4

3 3
1 2
2 3
3 1
start:any point
end:any point
path:1 2 3 1
*/
