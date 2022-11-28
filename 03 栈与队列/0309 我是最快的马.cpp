#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
#define pii pair<int, int>

int main()
{
    pii s, e;
    cin >> s.first >> s.second >> e.first >> e.second;

    int n;
    cin >> n;

    bool map[11][11] = {{0}};
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        map[x][y] = true;
    }

    int dis[11][11] = {{0}}, cnt[11][11] = {{0}};
    memset(dis, 0x3f, sizeof(dis));
    dis[s.first][s.second] = 0, cnt[s.first][s.second] = 1;

    string ans[11][11];
    ans[s.first][s.second] = "(0,0)";

    queue<pii> q;
    q.push(s);

    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}, dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    while (!q.empty())
    {
        pii cur = q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int x = cur.first, y = cur.second, xx = x + dx[i], yy = y + dy[i];
            if (xx < 0 || xx > 10 || yy < 1 || yy > 10 || map[xx][yy] || map[x + dx[i] / 2][y + dy[i] / 2])
                continue;
            if (dis[xx][yy] < dis[x][y] + 1) //按照dis大小分三类
                continue;
            else if (dis[xx][yy] == dis[x][y] + 1)
                cnt[xx][yy]++;
            else
                cnt[xx][yy] = 1, dis[xx][yy] = dis[x][y] + 1, ans[xx][yy] = ans[x][y] + "-(" + to_string(xx) + ',' + to_string(yy) + ')', q.push({xx, yy});
        }
    }
    cout << (cnt[e.first][e.second] == 1 ? ans[e.first][e.second] : to_string(cnt[e.first][e.second])) << endl;
}