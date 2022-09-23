#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    string tmp;
    map<string, multiset<string>> a; //一样的单词也要算数目！
    while (cin >> tmp)
    {
        string key = tmp;
        sort(key.begin(), key.end());
        a[key].insert(tmp);
    }
    for (int i = 0; i < 5 && !a.empty(); i++)
    {
        int max_size = -1;
        string max_key;
        multiset<string> max_set;
        for (auto j : a)
            if ((int)j.second.size() > max_size)
                max_size = j.second.size(), max_key = j.first, max_set = j.second;
            else if ((int)j.second.size() == max_size) //如果单词个数相同，要看set内的字典序
                if (*max_set.begin() > *j.second.begin())
                    max_key = j.first, max_set = j.second;
        a.erase(max_key);
        set<string> ans; //用来除重
        for (auto j : max_set)
            ans.insert(j);
        printf("Group of size %d: ", (int)max_set.size());
        for (auto j : ans)
            cout << j << ' ';
        cout << '.' << endl;
    }
}