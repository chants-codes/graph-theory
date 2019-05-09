//fleury algorithm
#include<cstring>
#include<iostream>
using namespace std;

int stk[1005];
//��ջ��ջ����ĿӦ�úͱߵ���Ŀһ����������ˡ�
int top;
int N,M;
int mp[1005][1005];

void dfs(int x){
    stk[top]=x;
    top++;//��ջ֮����ջ����һ
    for(int i=1;i<=N;i++){
        if(mp[x][i]){
            mp[x][i]=mp[i][x]=0;//ɾ���˱�
            dfs(i);
            break;
        }
    }
}

void fleury(int ss){
    top=0;
    stk[top]=ss;//��������Euler·����
    top++;//��ջ֮����ջ����һ������topָ���
    while(top>0){//while(!sta.empty())
        int brige=1;//����Ƿ�Ϊ��
        for(int i=1;i<=N;i++){//��ͼ����һ���߲��Ǹ��(��)
            if(mp[stk[top-1]][i]){//ע����ջ������top-1ָ��ջ����topָ���
                brige=0;
                break;
            }
        }
        top--;//ע����ջʱ��Ĳ����������һ�����԰��������
        if (brige) cout<<stk[top]<<" ";
        //ע�����������ŷ����·�Ƿ��˵ģ�������յ�
        //���û�е������չ���������ջ
        else dfs(stk[top]);//�����������ŷ��·��
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
        int ss=1;//��ʼ����㣬ע������һ��Ҫ��ʼ��
        //���ͼ����ȫ�����Ƕ�Ϊż���ĵ㣬��ô��Ҫ��ǰ�趨һ�����
        for(int i=1;i<=N;i++){
            int deg=0;
            for(int j=1;j<=N;j++){
                deg+=mp[i][j];
            }
            if(deg%2==1){
                ss=i;//�������ȵ�Ļ��͸���ss
                num++;
                cout<<i<<endl;//�����Ϊ�����ĵ�
            }
        }//�Ϸ����봦����Ƕȵ�����
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
