#include <iostream>
using namespace std;

int a[11][11] = {{0}};
int f(int m, int n)
{
    if (m == 1 || m == 0 || n == 1)
        return 1;
    else if (a[m][n])
        return a[m][n];
    if (m >= n)
        a[m][n] = f(m - n, n) + f(m, n - 1);
    else
        a[m][n] = f(m, n - 1);
    return a[m][n];
}
int main()
{

    int N;
    cin >> N;
    while (N--)
    {
        int m, n;
        cin >> m >> n;
        cout << f(m, n) << endl;
    }
}