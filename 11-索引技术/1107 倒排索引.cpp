#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main()
{
    int N, n;
    cin >> N;
    unordered_set<string> s[1001];
    for (int i = 1; i <= N; i++)
    {
        cin >> n;
        string tmp;
        while (n--)
            cin >> tmp, s[i].insert(tmp);
    }
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string tmp;
        cin >> tmp;
        bool ok = false;
        for (int j = 1; j <= N; j++)
            if (s[j].find(tmp) != s[j].end())
                cout << j << ' ', ok = true;
        cout << (ok ? "\n" : "NOT FOUND\n");
    }
}