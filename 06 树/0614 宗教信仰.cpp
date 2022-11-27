#include <iostream>
#include <set>
using namespace std;

int f[50001];
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
    int n, m, cnt = 0;
    while (cin >> n >> m && n)
    {
        for (int i = 1; i <= n; i++)
            f[i] = i;
        while (m--)
        {
            int x, y;
            cin >> x >> y;
            merge(x, y);
        }
        set<int> s;
        for (int i = 1; i <= n; i++)
            s.insert(find(i));
        printf("Case %d: ", ++cnt);
        cout << s.size() << endl;
    }
}