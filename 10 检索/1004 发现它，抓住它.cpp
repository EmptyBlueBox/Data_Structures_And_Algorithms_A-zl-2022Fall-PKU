#include <iostream>
using namespace std;

// 1~n:帮派A n+1~2n:帮派B f[i]=f[n+j]代表他们不是一个帮派
int f[200010];
int getf(int x)
{
    return (x == f[x] ? x : f[x] = getf(f[x]));
}
void merge(int x, int y)
{
    f[getf(x)] = getf(y);
}
int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int m, n;
        cin >> m >> n; //案件 信息
        for (int i = 1; i <= 2 * m; i++)
            f[i] = i;
        for (int i = 1; i <= n; i++)
        {
            char op;
            int x, y;
            cin >> op >> x >> y;
            if (op == 'D')
                merge(x, y + m), merge(x + m, y);
            else
            {
                if (getf(x) == getf(y))
                    cout << "In the same gang.\n";
                else if (getf(x) == getf(y + m) || getf(y) == getf(x + m))
                    cout << "In different gangs.\n";
                else
                    cout << "Not sure yet.\n";
            }
        }
    }
}