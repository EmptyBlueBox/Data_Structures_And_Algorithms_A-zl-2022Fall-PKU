#include <iostream>
#include <vector>
using namespace std;
//先用hash_table判断是否有有可能，再在所有可能中找是否真的有一样的
#define prime 999983
int info[100000][6];
vector<int> hash_table[prime];

bool is_similar(int x, int y)
{
    for (int delta = 0; delta < 6; delta++) //顺时针比较
    {
        for (int i = 0; i < 6; i++)
            if (info[x][i] != info[y][(i + delta) % 6])
                goto nxt_delta1;
        return true;
    nxt_delta1:;
    }
    for (int delta = 0; delta < 6; delta++) //逆时针比较
    {
        for (int i = 0; i < 6; i++)
            if (info[x][i] != info[y][(6 - i + delta) % 6])
                goto nxt_delta2;
        return true;
    nxt_delta2:;
    }
    return false;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < 6; j++)
            cin >> info[i][j], sum += info[i][j];
        for (auto j : hash_table[sum % prime])
            if (is_similar(i, j))
            {
                cout << "Twin snowflakes found.\n";
                return 0;
            }
        hash_table[sum % prime].push_back(i);
    }
    cout << "No two snowflakes are alike.\n";
}