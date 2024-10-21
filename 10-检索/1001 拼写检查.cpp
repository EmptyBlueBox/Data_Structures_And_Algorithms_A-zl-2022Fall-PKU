#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
using namespace std;

// 重载set<string>的比较，按照在字典中的位置比较
unordered_map<string, int> dict; //字典，并且用unordered_map储存是字典中的第几个，方便排序（但是map都占内存，不要求按顺序来就用unordered_map）
struct cmp
{
    bool operator()(const string &a, const string &b) const
    {
        return dict[a] < dict[b];
    }
};
void del(string &a, set<string, cmp> &ans)
{
    int len = a.length();
    for (int i = 0; i < len; i++)
    {
        string tmp = a;
        tmp.erase(i, 1);
        if (dict[tmp])
            ans.insert(tmp);
    }
}
void change(string &a, set<string, cmp> &ans)
{
    int len = a.length();
    for (int i = 0; i < len; i++)
    {
        string tmp = a;
        for (char c = 'a'; c <= 'z'; c++)
        {
            tmp[i] = c;
            if (dict[tmp])
                ans.insert(tmp);
        }
    }
}
void add(string &a, set<string, cmp> &ans)
{
    int len = a.length();
    for (int i = 0; i <= len; i++)
    {
        string tmp = a;
        tmp.insert(tmp.begin() + i, 'a'); //对于每一个位置只insert一次
        for (char c = 'a'; c <= 'z'; c++)
        {
            tmp[i] = c;
            if (dict[tmp])
                ans.insert(tmp);
        }
    }
}
void search(string a)
{
    set<string, cmp> ans; //找到所有的相似字符串并除重、排序
    if (dict[a])
    {
        cout << a << " is correct\n";
        return;
    }
    del(a, ans), change(a, ans), add(a, ans);
    cout << a << ":";
    for (auto &i : ans)
        cout << ' ' << i;
    cout << endl;
}
int main()
{
    int cnt = 0;
    string tmp;
    while (cin >> tmp && tmp != "#")
        dict[tmp] = ++cnt;
    while (cin >> tmp && tmp != "#")
        search(tmp);
}