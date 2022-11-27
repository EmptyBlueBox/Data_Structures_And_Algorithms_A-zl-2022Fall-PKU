#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

//二分SPFA或Dijkstra
#define SPFA
#define Dijkstra

#define pii pair<int, int>
int n, m, k;
bool no_path = false; //注意判断无路径-1
vector<pii> edge[1001];
// SPFA找1->n的最短路径，大于x算长度为1，最短路径<=k时该价钱可以建起来线路
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
        q.pop();             //与Dijkstra和Prim等贪心算法不同，SPFA是暴力松弛，不用判定是否非法
        in_queue[cur] = false;
        for (auto i : edge[cur])
            if (dis[i.second] > dis[cur] + (i.first > x)) //放入队列的条件：被松弛了且队列里没有
            {
                dis[i.second] = dis[cur] + (i.first > x); //松弛终点为i.second
                if (!in_queue[i.second])
                    q.push(i.second), in_queue[i.second] = true;
            }
    }
    if (dis[n] == 0x3f3f3f3f)
        no_path = true;
    return dis[n] <= k;

#elif Dijkstra

    // Dijkstra
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, 1});
    bool vis[1001] = {false};
    int dis[1001];
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    while (!q.empty())
    {
        int cur = q.top().second; //下一个扩入的节点，这个节点的距离只是用来贪心排序的，不用放进cur
        q.pop();
        if (vis[cur])
            continue;
        vis[cur] = true;
        for (auto i : edge[cur])                          //松弛一圈节点，被更新的放进队列
            if (dis[i.second] > dis[cur] + (i.first > x)) //放入队列的条件：被松弛了
                dis[i.second] = dis[cur] + (i.first > x), q.push({dis[i.second], i.second});
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