#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//使用邻接矩阵、入度表实现BFS拓扑排序，来判环
vector<int> edge[100001];
vector<int> id_table;
int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            edge[i].clear();
        id_table.clear();
        id_table.resize(n + 1, 0);
        while (m--)
        {
            int x, y;
            cin >> x >> y;
            edge[x].push_back(y);
            id_table[y]++;
        }
        queue<int> q; //入度为0的节点
        int cnt = 0;  //能拓扑排序出来的点的个数
        for (int i = 1; i <= n; i++)
            if (id_table[i] == 0)
                q.push(i);
        while (!q.empty())
        {
            int from = q.front();
            q.pop(), cnt++;
            for (auto to : edge[from])
                if (--id_table[to] == 0)
                    q.push(to);
        }
        cout << (cnt != n ? "Yes\n" : "No\n");
    }
}