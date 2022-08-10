#include <iostream>
using namespace std;

int main()
{
    int n, k, a[32][32] = {{0}}, dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0}, x = 1, y = 1, dir = 0;
    cin >> n >> k;
    for (int i = 1; i <= n * n; i++)
    {
        a[x][y] = i;
        if (a[x][y] == k)
        {
            cout << x << ' ' << y;
            return 0;
        }
        int xx = x + dx[dir], yy = y + dy[dir];
        if (xx < 1 || xx > n || yy < 1 || yy > n || a[xx][yy])
            dir = (dir + 1) % 4;
        x = x + dx[dir], y = y + dy[dir];
    }
}