#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    string a[10001], b[51];
    string s;
    int m = 0, n = 0;
    set<string> aa;
    while (cin >> s && s != "#")
        a[++m] = s, aa.insert(s);
    while (cin >> s && s != "#")
        b[++n] = s;
    for (int i = 1; i <= n; i++)
    {
        if (aa.find(b[i]) != aa.end())
        {
            printf("%s is correct\n", b[i].c_str());
            continue;
        }
        set<string> bb;
        for (int j = 0; j < (int)b[i].length(); j++)
        {
            string tmp = b[i];
            for (char k = 'a'; k <= 'z'; k++)
                tmp[j] = k, bb.insert(tmp);
            tmp.erase(j, 1), bb.insert(tmp); // string::erase(int pos, int len)，要写长度否则可能删完
        }
        for (int j = 0; j <= (int)b[i].length(); j++)
            for (char k = 'a'; k <= 'z'; k++)
            {
                string tmp = b[i];
                tmp.insert(j, 1, k), bb.insert(tmp);
            }
        printf("%s:", b[i].c_str());
        for (int j = 1; j <= m; j++)
            if (bb.find(a[j]) != bb.end())
                cout << ' ' << a[j];
        cout << endl;
    }
}