#include <iostream>
using namespace std;

int main()
{
    int n, a[40][40] = {{0}}, x, y;
    cin >> n;
    n = 2 * n - 1, x = 1, y = n / 2 + 1;
    for (int i = 1; i <= n * n; i++)
    {
        a[x][y] = i;
        if (a[x - 1][y + 1] || (x == 1 && y == n))
            x++;
        else if (x == 1)
            x = n, y++;
        else if (y == n)
            x--, y = 1;
        else
            x--, y++;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}