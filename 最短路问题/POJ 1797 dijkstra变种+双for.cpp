#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define ms(x, n) memset(x,n,sizeof(x));
typedef  long long LL;
const LL maxn = 1010;
const int inf = 1<<30;

int N, M, W[maxn][maxn];
int d[maxn];        //����i��������Сֵ
bool used[maxn];
int dijkstra(){
    ms(used, 0);
    for(int i = 1; i <= N; i++)
        d[i] = W[1][i]; //��ʼ��d
    used[1] = true;

    while(true){
        int u = 0, curMax = 0;
        for(int i = 1; i <= N; i++)
            if(!used[i] && d[i]>curMax)
                curMax = d[i], u = i;

        if(u == 0) break;
        used[u] = true;
        for(int v = 1; v <= N; v++)
            if(!used[v])
                d[v] = max(min(curMax, W[u][v]), d[v]);
    }
    return d[N];
}
int main()
{
    int T, u, v, w;
    cin >> T;
    for(int t = 1; t <= T; t++){
        ms(W, 0);
        cin >> N >> M;
        for(int i = 1; i <= M; i++){
            cin >> u >> v >> w;
            W[u][v] = W[v][u] = w;
        }

        cout << "Scenario #"<< t <<":" <<endl;
        cout << dijkstra() << endl << endl;
    }

	return 0;
}