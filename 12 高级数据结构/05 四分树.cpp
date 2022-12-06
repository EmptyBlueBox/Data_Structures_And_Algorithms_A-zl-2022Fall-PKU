#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int n, presum[512][512];
void cal_presum()
{
    for (int i = 1; i < n; i++)
        presum[0][i] += presum[0][i - 1], presum[i][0] += presum[i - 1][0];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            presum[i][j] += presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1];
}
int get_presum(int x, int y)
{
    if (x == -1 || y == -1)
        return 0;
    else
        return presum[x][y];
}
// x2与y2取不到
//返回-1：不全一样
//返回0：全是0
//返回1：全是1
int all_same(int x1, int y1, int x2, int y2)
{
    x1--, y1--, x2--, y2--; //注意presum是取等的位置
    int dx = x2 - x1, dy = y2 - y1;
    int sum = get_presum(x2, y2) - get_presum(x1, y2) - get_presum(x2, y1) + get_presum(x1, y1);
    if (sum == 0)
        return 0;
    else if (sum == dx * dy)
        return 1;
    else
        return -1;
}
string layer_ans[12]; //每一层合起来的字符串
void f(int layer, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 || y1 == y2)
        return;
    int midx = (x1 + x2) >> 1, midy = (y1 + y2) >> 1;
    int sq[4], loc[4][4] = {{x1, y1, midx, midy}, {x1, midy, midx, y2}, {midx, y1, x2, midy}, {midx, midy, x2, y2}};
    for (int i = 0; i < 4; i++)
        sq[i] = all_same(loc[i][0], loc[i][1], loc[i][2], loc[i][3]);
    for (int i = 0; i < 4; i++)
        if (sq[i] == 0)
            layer_ans[layer] += "00";
        else if (sq[i] == 1)
            layer_ans[layer] += "01";
        else
            layer_ans[layer] += "1";
    for (int i = 0; i < 4; i++)
        if (sq[i] == -1)
            f(layer + 1, loc[i][0], loc[i][1], loc[i][2], loc[i][3]);
}
int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        cin >> n;
        int has_1 = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> presum[i][j], has_1 = max(has_1, presum[i][j]);
        if (has_1 == 0)
        {
            cout << 0 << endl;
            continue;
        }
        string ans = "1";
        cal_presum();
        f(0, 0, 0, n, n);
        for (int i = 0; i < 12; i++)
            ans += layer_ans[i], layer_ans[i].clear();
        cout << setbase(16) << setiosflags(ios::uppercase) << strtol(ans.c_str(), NULL, 2) << endl;
    }
}