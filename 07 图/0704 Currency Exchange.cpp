#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define pii pair<int, int>
#define pip pair<int, pair<int, int>>
#define pipdd pair<int, pair<double, double>>

// SPFA判环，queue存将要松弛的节点，使用vector模拟邻接表
// 通过松弛维护一个最短路径（最多钱数）数组
// 找最小路返回是否有负环，找最大路返回是否有正环（如本题）
int main()
{
    int n, m, src;
    double ori;
    cin >> n >> m >> src >> ori;
    vector<pipdd> edge[1001];
    for (int i = 0; i < n; i++)
    {
        int f, t;
        double r1, c1, r2, c2;
        cin >> f >> t >> r1 >> c1 >> r2 >> c2;
        edge[f].push_back({t, {r1, c1}}), edge[t].push_back({f, {r2, c2}});
    }
    queue<int> q;
    q.push(src);
    bool in_q[1001] = {false};
    double max_money[1001];
    memset(max_money, 0xc0, sizeof(max_money));
    max_money[src] = ori;
    //如果某个节点入队了n次，说明有正环，但是不一定回到源点。回到源点的判断比较简单，只需判断max_money[s]是否变大即可
    // int vis_num[101]={0};
    // vis_num[s] = 1;
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        in_q[f] = false;
        for (auto &i : edge[f])
        {
            int t = i.first;
            double xr = i.second.first, cms = i.second.second, after = (max_money[f] - cms) * xr;
            if (max_money[t] < after)
            {
                max_money[t] = after;
                if (!in_q[t])
                    q.push(t), in_q[t] = true;
                if (t == src) //源点钱可能增加就说明可以得到更多的钱
                {
                    cout << "YES\n";
                    return 0;
                }
            }
        }
    }
    cout << "NO\n";
    return 0;
}