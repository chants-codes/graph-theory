#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1010;
int n, m;
struct Edge
{
    int s, e, v;
} ed[maxn * maxn];

int a[maxn];
void Init()
{
    for(int i = 1; i <= n ; i++)
    {
        a[i] = i;
    }
}
int findf(int x)
{
    if(a[x] == x)
    {
        return a[x];
    }
    return a[x] = findf(a[x]);
}

bool mag(int x, int y)
{
    int fx = findf(x);
    int fy = findf(y);
    if(fx == fy)
    {
        return false;
    }
    a[fx] = fy;
    return true;
}

bool cmp(Edge A, Edge B)
{
    return A.v > B.v;
}

int main()
{
    int _, cas = 0;
    scanf("%d", &_);
    while(_--)
    {
        scanf("%d%d" , &n, &m);
        cas++;
        Init();
        for(int i = 0; i < m ; i++)
        {
            scanf("%d%d%d", &ed[i].s, &ed[i].e, &ed[i].v);
        }
        sort(ed, ed + m , cmp);
        int wanted = 0;
        for(int i = 0; i < m; i++)
        {
            if(mag(ed[i].s, ed[i].e))
            {
                if(findf(1) == findf(n))
                {
                    wanted = ed[i].v;
                    break;
                }
            }
        }
        printf("Scenario #%d:\n%d\n\n", cas, wanted);
    }
    return 0;
}