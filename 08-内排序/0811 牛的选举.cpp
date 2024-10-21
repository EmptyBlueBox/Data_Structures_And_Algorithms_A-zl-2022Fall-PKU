#include <iostream>
#include <queue>
using namespace std;
#define pipii pair<int, pair<int, int>>

#define int long long
signed main()
{
    int n, k;
    cin >> n >> k;
    priority_queue<pipii, vector<pipii>, greater<pipii>> q;
    for (int i = 1; i <= n; i++)
    {
        pipii tmp;
        cin >> tmp.first >> tmp.second.first;
        tmp.second.second = i;
        if (q.size() < k)
            q.push(tmp);
        else if (q.top() < tmp)
            q.pop(), q.push(tmp);
    }
    int ans = 0, max_second_stage = 0xc0c0c0c0c0c0c0c0;
    while (!q.empty())
    {
        if (q.top().second.first > max_second_stage)
            max_second_stage = q.top().second.first, ans = q.top().second.second;
        q.pop();
    }
    cout << ans << endl;
}