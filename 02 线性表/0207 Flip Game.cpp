#include <iostream>
using namespace std;
// 0是白，1是黑，全变成一个颜色；1是按，0不按
int ori[6][6] = {{0}}, push[6][6];
int ok()
{
    int cnt1 = 0, cnt2 = 0;
    for (int i = 2; i <= 5; i++) //全按成白的
        for (int j = 1; j <= 4; j++)
        {
            push[i][j] = ori[i - 1][j] ^ push[i - 1][j - 1] ^ push[i - 1][j] ^ push[i - 1][j + 1] ^ push[i - 2][j]; //(i,j)按or不按，能让ori[i-1][j]变成白色
            cnt1 += push[i][j];
        }
    for (int i = 1; i <= 4; i++)
        if (push[5][i])
            cnt1 = 0x3f3f3f3f;
    for (int i = 2; i <= 5; i++) //全按成黑的
        for (int j = 1; j <= 4; j++)
        {
            push[i][j] = ori[i - 1][j] ^ push[i - 1][j - 1] ^ push[i - 1][j] ^ push[i - 1][j + 1] ^ push[i - 2][j] ^ 1; //把(i,j)反过来按能让ori[i-1][j]变成黑的
            cnt2 += push[i][j];
        }
    for (int i = 1; i <= 4; i++)
        if (push[5][i])
            cnt2 = 0x3f3f3f3f;
    return min(cnt1, cnt2);
}
int main()
{
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            char c;
            cin >> c;
            if (c == 'b')
                ori[i][j] = 1;
        }
    for (int i = 0; i < (1 << 4); i++)
    {
        int cnt = 0;
        for (int j = 1; j <= 4; j++)
            push[1][j] = ((i >> (j - 1)) & 1), cnt += push[1][j];
        cnt += ok();
        ans = min(ans, cnt);
    }
    cout << (ans >= 0x3f3f3f3f ? "Impossible" : to_string(ans)) << endl;
}