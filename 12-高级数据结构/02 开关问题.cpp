#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n, eq[32] = {0}, tmp, x, y;
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> tmp, eq[i] |= tmp << n, eq[i] |= 1 << i; //自己按自己也要变
        for (int i = 0; i < n; i++)
            cin >> tmp, eq[i] ^= tmp << n;
        while (cin >> x >> y && x && y)
            eq[y - 1] |= 1 << (x - 1);
        //对eq进行高斯消元
        int row = 0;                                        //最新的方程是哪一行
        for (int col = 0; col < n && row < n; col++, row++) //每次处理一列
        {
            int i = row;
            while (i < n && !(eq[i] & (1 << col)))
                i++;
            if (i == n) // c处变量全是0，这行方程多一格0
            {
                row--;
                continue;
            }
            if (i > row) //交换两个方程
                swap(eq[row], eq[i]);
            for (int j = row + 1; j < n; j++)
                if (eq[j] & (1 << col))
                    eq[j] ^= eq[row];
        }
        //高斯消元之后eq[row]应该是第一个全0方程
        for (int i = row; i < n; i++)
            if (eq[i] & (1 << n)) //化简的增广阵中存在(0, 0, ..., a)这样的行，无解！
            {
                cout << "Oh,it's impossible~!!\n"; // Oh之后没有空格
                goto loop;
            }
        cout << (1 << (n - row)) << endl;
    loop:;
    }
}