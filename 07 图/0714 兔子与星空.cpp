#include <iostream>
#include <queue>
#include <set>
using namespace std;

//最小生成树
struct edge
{
    int from, to, weight;
    bool operator<(const edge &other) const
    {
        return weight > other.weight;
    }
};
int fa[26];
int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    fa[find(x)] = find(y);
}
int main()
{
    for (int i = 0; i < 26; i++) //初始化父亲数组
        fa[i] = i;
    priority_queue<edge> s; //用来每次找最小边权的边，尽量不要用set，不方便删除
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        char tmp;
        int cnt;
        cin >> tmp >> cnt;
        while (cnt--)
        {
            char c;
            int weight;
            cin >> c >> weight;
            s.push({i, c - 'A', weight});
        }
    }
    int ans = 0;
    while (!s.empty()) //每次看最小边权的边是否连接两个等价类
    {
        edge now = s.top();
        s.pop();
        int ff = find(now.from), ft = find(now.to);
        if (ff == ft)
            continue;
        merge(ff, ft);
        ans += now.weight;
    }
    cout << ans << endl;
}