#include <iostream>
using namespace std;

unsigned int info[100000];
int main()
{
    int m, n, op;
    char c;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        cin >> info[i];
    //数据不harsh，双重循环即可
    while (n--)
    {
        cin >> c >> op;
        if (c == 'C')
            for (int i = 0; i < m; i++)
                info[i] += op;
        else
        {
            int cnt = 0;
            for (int i = 0; i < m; i++)
                cnt += ((info[i] >> op) & 1);
            cout << cnt << endl;
        }
    }
}