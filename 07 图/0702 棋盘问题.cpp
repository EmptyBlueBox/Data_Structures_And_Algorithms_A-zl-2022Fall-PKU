#include <iostream>
using namespace std;

int n, k, a[8][8] = {{0}}, ans = 0;
bool col_occupied[8] = {false};
void f(int row, int used)
{
    if (used == k)
    {
        ans++;
        return;
    }
    else if (row == n)
        return;
    for (int i = 0; i < n; i++)
        if (a[row][i] && !col_occupied[i])
            col_occupied[i] = true, f(row + 1, used + 1), col_occupied[i] = false;
    f(row + 1, used);
}
int main()
{
    while (cin >> n >> k && n != -1)
    {
        ans = 0;
        char c;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> c, a[i][j] = c == '#';
        f(0, 0);
        cout << ans << endl;
    }
}