#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n + 1);                     //存边
    vector<int> in(n + 1, 0);                         //入度表
    priority_queue<int, vector<int>, greater<int>> q; //用来每一次找序号最小的入度为0的点（set也可以）
    for (int i = 0; i < m; i++)                       //初始化边与入度表
    {
        int f, t;
        cin >> f >> t;
        e[f].push_back(t);
        in[t]++;
    }
    for (int i = 1; i <= n; i++) //初始化存入度为0的节点的优先队列
        if (!in[i])
            q.push(i);
    while (!q.empty())
    {
        int now = q.top(); //每次删除一个入度为0的节点
        cout << 'v' << now << ' ';
        q.pop();
        for (auto i : e[now]) //出边指向的节点入度--，如果这个节点入度变成0就进队列
        {
            in[i]--;
            if (!in[i])
                q.push(i);
        }
    }
}