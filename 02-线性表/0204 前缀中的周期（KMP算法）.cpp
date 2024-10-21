#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n, cnt = 0;
    while (cin >> n && n)
    {
        string a;
        cin >> a;
        vector<int> nxt(n + 1);
        nxt[0] = -1;
        int i = 0, j = -1;
        while (i < n)
            if (j == -1 || a[i] == a[j])
                nxt[++i] = ++j;
            else
                j = nxt[j];
        cout << "Test case #" << ++cnt << endl;
        for (int i = 1; i <= n; i++)
            if (i % (i - nxt[i]) == 0 && nxt[i])
                cout << i << ' ' << i / (i - nxt[i]) << endl;
        cout << endl;
    }
}