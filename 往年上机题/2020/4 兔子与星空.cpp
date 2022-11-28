#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//最小生成树 Prim(Dijkstra)
int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> edge[26];
    for (int i = 0; i < n - 1; i++)
    {
        char from;
        int e_cnt;
        cin >> from >> e_cnt;
        while (e_cnt--)
        {
            char to;
            int w;
            cin >> to >> w;
            edge[from - 'A'].push_back({w, to - 'A'});
            edge[to - 'A'].push_back({w, from - 'A'});
        }
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 0});         //距离已有的生成树距离为0,顶点0，first是到已有spanning tree的权值顺序不能反！！！
    bool vis[26] = {false}; //顶点0此时还不在生成树里
    int ans = 0;
    while (!q.empty())
    {
        pair<int, int> nxt = q.top();
        q.pop();
        // 与BFS不同在于拿出来才新节点检查是否合法，因为可能在这个node被加入队列之后该顶点被别的更近的node访问了
        // 因此不能在加入push之前检查合法性，要在pop之后检查
        // push的时候把所有的相连边都push就行
        if (vis[nxt.second] == true)
            continue;
        vis[nxt.second] = true;
        ans += nxt.first;
        for (auto i : edge[nxt.second]) //生成树不用判断距离小于原距离，因为根本没有距离这个概念
            if (!vis[i.second])         //把所有不在生成树中的节点与节点和生成树的可能最短距离放入队列
                q.push(i);
    }
    cout << ans << endl;
}