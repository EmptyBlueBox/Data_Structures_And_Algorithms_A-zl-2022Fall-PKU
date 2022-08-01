#include <iostream>
#include <map>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        map<int, int, greater<int>> cnt;
        int a, b;
        while (cin >> a >> b && b >= 0)
            cnt[b] += a;
        while (cin >> a >> b && b >= 0)
            cnt[b] += a;
        for (auto i : cnt)
            if (i.second)
                cout << "[ " << i.second << ' ' << i.first << " ] ";
        cout << endl;
    }
}