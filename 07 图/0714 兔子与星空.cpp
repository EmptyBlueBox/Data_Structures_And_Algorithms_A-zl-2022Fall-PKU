#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define pip pair<int, pair<int, int>>

int f[128];
int find(int x)
{
    return (x == f[x] ? x : f[x] = find(f[x]));
}
void merge(int x, int y)
{
    f[find(y)] = find(x);
}

int main()
{
    for (int i = 0; i < 128; i++)
        f[i] = i;
    int n;
    cin >> n;
    priority_queue<pip, vector<pip>, greater<pip>> q;
    for (int i = 1; i < n; i++)
    {
        char f;
        int cnt;
        cin >> f >> cnt;
        for (int i = 0; i < cnt; i++)
        {
            char t;
            int w;
            cin >> t >> w;
            q.push({w, {f, t}});
        }
    }
    int ans = 0;
    while (!q.empty())
    {
        int w = q.top().first, x = q.top().second.first, y = q.top().second.second;
        q.pop();
        if (find(x) != find(y))
            ans += w, merge(x, y);
    }
    cout << ans << endl;
}