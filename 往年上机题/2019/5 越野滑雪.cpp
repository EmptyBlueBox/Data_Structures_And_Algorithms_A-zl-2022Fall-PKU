#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

//二分BFS
#define pii pair<int, int>
int n, m, info[502][502] = {{0}}, dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
bool check_point[502][502] = {{0}};
pii start;
bool connect(int d)
{
    queue<pii> q;
    q.push(start);
    bool vis[502][502] = {{false}};
    vis[start.first][start.second] = true;
    while (!q.empty())
    {
        pii cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int xx = cur.first + dx[i], yy = cur.second + dy[i];
            if (vis[xx][yy] || abs(info[xx][yy] - info[cur.first][cur.second]) > d)
                continue;
            vis[xx][yy] = true; //放入队列时更新距离（vis）
            q.push({xx, yy});
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (check_point[i][j] && !vis[i][j])
                return false;
    return true;
}

int main()
{
    int l = -1, r = 0xc0c0c0c0, mid;
    memset(info, 0xc0, sizeof(info)); //周围一圈不可能走到
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> info[i][j];
            r = max(r, info[i][j] + 1);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> check_point[i][j];
            start = make_pair(i, j);
        }
    while (l + 1 != r)
    {
        mid = l + (r - l) / 2;
        if (connect(mid))
            r = mid;
        else
            l = mid;
    }
    cout << r << endl;
}