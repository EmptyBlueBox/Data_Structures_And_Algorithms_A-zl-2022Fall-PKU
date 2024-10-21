#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define pis pair<int, string>
struct cmp
{
    bool operator()(const pis &a, const pis &b) const
    {
        return (a.first != b.first ? a.first > b.first : a.second < b.second);
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
    map<pis, set<string>, cmp> sort_groups; //先比较字符串个数再比较第一个字符串大小，同时对字符串集合除重
    for (auto i : dict)
    {
        pis key = {i.second.size(), *i.second.begin()};
        for (auto j : i.second)
            sort_groups[key].insert(j);
    }
    for (int i = 0; i < 5; i++)
    {
        int cnt = (*sort_groups.begin()).first.first;
        set<string> ans = (*sort_groups.begin()).second;
        sort_groups.erase(sort_groups.begin());
        printf("Group of size %d: ", cnt);
        for (auto j : ans)
            cout << j << ' ';
        cout << ".\n";
    }
}