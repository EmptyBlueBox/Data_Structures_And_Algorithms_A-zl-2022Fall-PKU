#include <iostream>
#include <vector>
using namespace std;

//等价类永远是同一种动物
//将x,x+n,x+2n看成互不相同的元素，x+n代表一个x的虚拟天敌，在1~n的实际存在的个体中不存在
//[n+1,2n]、[2n+1,3n]只起辅助作用，其中元素并不存在
//如果发现x是y的天敌，那么可以确定x和y+n（虚拟天敌）是一种动物，则可以将它们并在一起
#define N 50000
int f[N * 3 + 1];
int find(int x)
{
    return (x == f[x] ? x : f[x] = find(f[x]));
}
void merge(int x, int y)
{
    f[find(y)] = find(x);
}
int main()
{
    for (int i = 1; i <= N * 3; i++)
        f[i] = i;
    int n, k, ans = 0;
    cin >> n >> k;
    while (k--)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (x > n || y > n)
        {
            ans++;
            continue;
        }
        if (op == 1)
        {
            if (find(x) == find(y + n) || find(x) == find(y + 2 * n))
            {
                ans++;
                continue;
            }
            merge(x, y), merge(x + n, y + n), merge(x + 2 * n, y + 2 * n);
        }
        else
        {
            if (x == y || find(x) == find(y) || find(x) == find(y + 2 * n))
            {
                ans++;
                continue;
            }
            merge(x, y + n), merge(x + n, y + 2 * n), merge(x + 2 * n, y);
        }
    }
    cout << ans << endl;
}