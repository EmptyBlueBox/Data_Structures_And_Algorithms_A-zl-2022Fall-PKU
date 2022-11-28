#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class KEY
{
public:
    int cnt;      //一组字符串的个数（有重个数）
    string first; //第一个字符串，在字符串个数一样的时候用来比较
    KEY(int _cnt, string _first) : cnt(_cnt), first(_first) {}
    bool operator<(const KEY &a) const
    {
        return (cnt != a.cnt ? cnt > a.cnt : first < a.first);
    }
};

int main()
{
    map<string, multiset<string>> dict; //字母数量一样的有重等价类
    string cur;
    while (cin >> cur)
    {
        string key = cur;
        sort(key.begin(), key.end());
        dict[key].insert(cur);
    }
    map<KEY, set<string>> sort_groups; //先比较字符串个数再比较第一个字符串大小，同时对字符串集合除重
    for (auto i : dict)
    {
        KEY key(i.second.size(), *i.second.begin());
        for (auto j : i.second)
            sort_groups[key].insert(j);
    }
    for (int i = 0; i < 5; i++)
    {
        int cnt = (*sort_groups.begin()).first.cnt;
        set<string> ans = (*sort_groups.begin()).second;
        sort_groups.erase(sort_groups.begin());
        printf("Group of size %d: ", cnt);
        for (auto j : ans)
            cout << j << ' ';
        cout << ".\n";
    }
}