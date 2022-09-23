#include <iostream>
#include <string>
#include <queue>
using namespace std;

int dx[8] = {-1, -2, -2, -2, 1, 2, 2, 1}, dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int main()
{
    int map[11][11][3] = {{{0}}}; //最短距离，有几种方案，有无其它棋子
    string ans[11][11];           //最短方案是什么
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            map[i][j][0] = 0x3f3f3f3f, map[i][j][1] = 0;
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    map[sx][sy][0] = 0, map[sx][sy][1] = 1, ans[sx][sy] = "(0,0)";
    int N;
    cin >> N;
    while (N--)
    {
        int ox, oy;
        cin >> ox >> oy;
        map[ox][oy][2] = 1;
    }
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while (!q.empty())
    {
        int nx = q.front().first, ny = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int xx = nx + dx[i], yy = ny + dy[i];
            //超出范围，有棋子，别马腿
            if (xx < 0 || xx > 10 || yy < 0 || yy > 10 || map[xx][yy][2] || map[nx + dx[i] / 2][ny + dy[i] / 2][2])
                continue;
            if (map[xx][yy][0] < map[nx][ny][0] + 1)
                continue;
            else if (map[xx][yy][0] == map[nx][ny][0] + 1)
                map[xx][yy][1]++;
            else
                map[xx][yy][0] = map[nx][ny][0] + 1, map[xx][yy][1] = 1, ans[xx][yy] = ans[nx][ny] + "-(" + to_string(xx) + "," + to_string(yy) + ")", q.push({xx, yy});
        }
    }
    cout << (map[ex][ey][1] == 1 ? ans[ex][ey] : to_string(map[ex][ey][1])) << endl;
}