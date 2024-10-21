#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main()
{
    vector<string> lib;
    map<string, int> pre_cnt; //所有前缀出现的次数
    string a;
    while (cin >> a)
    {
        lib.push_back(a);
        int len = a.length();
        for (int i = 1; i <= len; i++)
            pre_cnt[a.substr(0, i)]++;
    }
    for (auto i : lib)
    {
        int len = i.length();
        for (int j = 1; j <= len; j++)
        {
            string prefix = i.substr(0, j);
            if (pre_cnt[prefix] == 1)
            {
                cout << i << ' ' << prefix << endl;
                goto loop;
            }
        }
        cout << i << ' ' << i << endl;
    loop:;
    }
}