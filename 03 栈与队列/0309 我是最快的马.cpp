#include <iostream>
#include <iomanip>
#include <cstring>
#include <queue>

using namespace std;

#define pos pair<int,int>

int main() {
    pos s, e;
    cin >> s.first >> s.second >> e.first >> e.second;
    int n;
    cin >> n;

    bool map[11][11] = { {0} };


    // 广度优先搜索
    int dis[11][11] = { {0} };
    int cnt[11][11] = { {0} };

    memset(dis, 0x3f, sizeof(dis));

    // 记录路径，只用存一条即可
    string ans[11][11];

    // 读取障碍物
    for (int i = 0;i < n;i++) {
        int x, y;
        cin >> x >> y;
        map[x][y] = true;
        dis[x][y] = 0;
    }
    map[s.first][s.second] = true;
    dis[s.first][s.second] = 0;
    ans[s.first][s.second] = "(" + to_string(s.first) + "," + to_string(s.second) + ")";

    int dx[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
    int dy[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };

    // 广度优先搜索，q记录所有最优步数为当前轮的点，FIFO先进先出，当一轮遍历完毕后也就全部被移除，开启下一轮，终止条件是q为空，也即所有点都被遍历过
    queue<pos> q;
    q.push(s);

    while (!q.empty()) {
        pos cur = q.front();
        int x = cur.first, y = cur.second;
        q.pop();
        // 遍历八个方向
        for (int i = 0;i < 8;i++) {
            // 判断是否超出边界
            int nx = cur.first + dx[i], ny = cur.second + dy[i];
            if (nx < 0 || nx > 10 || ny < 0 || ny > 10)
                continue;
            // 判断是否憋马腿、目标点已被占用
            if (map[cur.first + dx[i] / 2][cur.second + dy[i] / 2] || map[nx][ny])
                continue;
            // 判断是否可以替换为更优解/增加到达点的路径数
            // 并非更优解，也不能增加路径数，直接跳过
            if (dis[nx][ny] <= dis[x][y]) {
                continue;
            }
            // 并非更优解，但可以增加路径数，更新路径数
            else if (dis[nx][ny] == dis[x][y] + 1) {
                cnt[nx][ny] += cnt[x][y];
            }
            // 是更优解
            else {
                cnt[nx][ny] = 1;
                dis[nx][ny] = dis[x][y] + 1;
                ans[nx][ny] = ans[x][y] + "-(" + to_string(nx) + "," + to_string(ny) + ")";
                // 添加到队列中，等待下一轮遍历
                q.push({ nx,ny });
            }
        }
    }
    /*
    // 输出map
    cout << "map" << endl;
    for (int i = 0;i <= 10;i++) {
        for (int j = 0;j <= 10;j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---" << endl;

    // 输出dis
    cout << "dis" << endl;
    for (int i = 0;i <= 10;i++) {
        for (int j = 0;j <= 10;j++) {
            cout << dis[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---" << endl;

    // 输出cnt
    cout << "cnt" << endl;
    for (int i = 0;i <= 10;i++) {
        for (int j = 0;j <= 10;j++) {
            cout << cnt[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---" << endl;
    */
    // 输出
    cout << (cnt[e.first][e.second] == 1 ? ans[e.first][e.second] : to_string(cnt[e.first][e.second])) << endl;
}
