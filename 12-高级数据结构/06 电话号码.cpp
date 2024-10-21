#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        vector<string> lib;
        set<string> pre;
        for (int i = 0; i < n; i++)
        {
            string a;
            cin >> a;
            lib.push_back(a);
            int len = a.length();
            for (int j = 1; j < len; j++)
                pre.insert(a.substr(0, j));
        }
        for (auto i : lib)
            if (pre.find(i) != pre.end())
            {
                cout << "NO\n";
                goto loop;
            }
        cout << "YES\n";
    loop:;
    }
}