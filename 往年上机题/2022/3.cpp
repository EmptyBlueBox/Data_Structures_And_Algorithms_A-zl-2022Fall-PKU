#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
#define int long long
#define pii pair<int, int>
#define pipii pair<int, pair<int, int>>
#define ppiipii pair<pair<int, int>, pair<int, int>>

int f[100010], cnt[100010];
int find(int x)
{
    return (x == f[x] ? x : f[x] = find(f[x]));
}
void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    f[fx] = fy;
    cnt[fy] += cnt[fx];
}
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        f[i] = i, cnt[i] = 1;
    priority_queue<pipii, vector<pipii>, greater<pipii>> q;
    for (int i = 1; i < n; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        q.push({w, {a, b}});
    }
    int ans = 0;
    while (!q.empty())
    {
        pipii cur = q.top();
        q.pop();
        ans += cur.first;
        int fx = find(cur.second.first), fy = find(cur.second.second);
        ans += (cnt[fx] * cnt[fy] - 1) * (cur.first + 1);
        merge(fx, fy);
    }
    cout << ans << endl;
}