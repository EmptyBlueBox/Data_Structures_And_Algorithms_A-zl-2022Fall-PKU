#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

//二分SPFA或Dijkstra
#define SPFA
// #define Dijkstra

#define pii pair<int, int>
int n, m, k;
bool no_path = false; //注意判断无路径-1
vector<pii> edge[1001];
// 找1->n的最短路径，大于x算长度为1，最短路径<=k时该价钱可以建起来线路
bool possible_price(int x)
{

#ifdef SPFA

    // SPFA
    queue<int> q;
    q.push(1);
    bool in_queue[1001] = {false};
    in_queue[1] = true;
    int dis[1001];
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    while (!q.empty())
    {
        int cur = q.front(); //下一个用来作为松弛起点的点
        q.pop();             //与Dijkstra和Prim等贪心算法不同，SPFA是一直松弛，不用判定是否非法（指已有最短路径）
        in_queue[cur] = false;
        for (auto e : edge[cur])
            if (dis[e.second] > dis[cur] + (e.first > x)) //可以被松弛
            {
                dis[e.second] = dis[cur] + (e.first > x);
                if (!in_queue[e.second]) //如果队列中没有松弛终点，那么把松弛终点放入队列
                    q.push(e.second), in_queue[e.second] = true;
            }
    }
    if (dis[n] == 0x3f3f3f3f)
        no_path = true;
    return dis[n] <= k;

#endif

#ifdef Dijkstra

    // Dijkstra
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, 1});
    int dis[1001]; //最开始没有有最短路径的点，不要初始化dis[0] = 0
    memset(dis, 0x3f, sizeof(dis));
    while (!q.empty())
    {
        int cur = q.top().second;   //下一个扩入的节点，这个节点的距离只是用来贪心排序的，不用放进cur
        if (dis[cur] != 0x3f3f3f3f) //贪心算法一定先判断是否已经有了最短路径，因为可能许多一样的节点有不同的距离都在队列里
        {
            q.pop(); //没用的节点一定要pop
            continue;
        }
        dis[cur] = q.top().first; //找到最短路径之后再更新dis
        q.pop();
        for (auto e : edge[cur])             //查看一圈节点
            if (dis[e.second] == 0x3f3f3f3f) //把所有未产生最短路径的节点与其可能的最短路径放入队列
                q.push({dis[cur] + (e.first > x), e.second});
    }
    if (dis[n] == 0x3f3f3f3f)
        no_path = true;
    return dis[n] <= k;

#endif
}

int main()
{
    cin >> n >> m >> k;
    int l = -1, r = -1, mid = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        edge[a].push_back({w, b});
        edge[b].push_back({w, a});
        r = max(r, w + 1);
    }
    while (l + 1 != r)
    {
        mid = l + (r - l) / 2;
        if (possible_price(mid))
            r = mid;
        else
            l = mid;
    }
    cout << (no_path ? -1 : r) << endl;
}