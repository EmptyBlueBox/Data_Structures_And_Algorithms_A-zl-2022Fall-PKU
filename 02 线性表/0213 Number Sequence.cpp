#include <iostream>
using namespace std;

int a[50000] = {0}, b[50000] = {0}; // 序列1...i的位数和数字i的位数
int main()
{
    for (int i = 1; i < 50000; i++)
        b[i] = to_string(i).length(), a[i] = a[i - 1] + b[i];
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        for (int i = 1; i < 50000; i++) //枚举每一个1...i序列
            if (n <= a[i])
                for (int j = 1; j < 50000; j++) //如果在1...i序列中，枚举1...i序列里每一个数字j
                    if (n <= b[j])
                    {
                        cout << to_string(j)[n - 1] << endl;
                        goto loop;
                    }
                    else
                        n -= b[j];
            else
                n -= a[i];
    loop:;
    }
}