#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

unordered_map<string, int> lib;
unordered_set<string> similar; //除重
vector<string> ans;            //按顺序输出的答案
bool cmp(const string a, const string b)
{
    return lib[a] < lib[b];
}
void find_del(string a)
{
    int len = a.length();
    for (int i = 0; i < len; i++)
    {
        string tmp = a;
        tmp.erase(i, 1);
        if (lib[tmp])
            similar.insert(tmp);
    }
}
void find_replace(string a)
{
    int len = a.length();
    string tmp = a;
    for (int i = 0; i < len; i++)
    {
        for (char j = 'a'; j <= 'z'; j++)
        {
            tmp[i] = j;
            if (lib[tmp])
                similar.insert(tmp);
        }
        tmp[i] = a[i];
    }
}
void find_add(string a)
{
    int len = a.length();
    for (int i = 0; i <= len; i++)
    {
        string tmp = a;
        tmp.insert(tmp.begin() + i, 'a');
        for (char j = 'a'; j <= 'z'; j++)
        {
            tmp[i] = j;
            if (lib[tmp])
                similar.insert(tmp);
        }
    }
}
void search(string &a)
{
    if (lib[a])
    {
        cout << a << " is correct\n";
        return;
    }
    similar.clear(), ans.clear();
    find_del(a);
    find_replace(a);
    find_add(a);
    for (auto &i : similar)
        ans.push_back(i);
    sort(ans.begin(), ans.end(), cmp);
    cout << a << ':';
    for (auto &i : ans)
        cout << ' ' << i;
    cout << endl;
}
int main()
{
    int cnt = 0;
    string tmp;
    while (cin >> tmp && tmp != "#")
        lib[tmp] = ++cnt;
    while (cin >> tmp && tmp != "#")
        search(tmp);
}