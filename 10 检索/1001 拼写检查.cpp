// 重载字符串的比较，按照在字典中的位置比较
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
unordered_map<string, int> dict; //字典，并且用unordered_map储存是字典中的第几个，方便排序（但是map都占内存，不要求按顺序来就用unordered_mao）
unordered_set<string> similars;  //找到所有的相似字符串并除重
vector<string> ans;              //对set<string>重载<比较麻烦，放进vector再sort

bool cmp(const string a, const string b)
{
    return dict[a] < dict[b];
}

void del_redundant(string tolookup)
{
    int l = tolookup.length();
    for (int i = 0; i < l; i++)
    {
        string tmp = tolookup;
        tmp.erase(i, 1);
        if (dict[tmp])
            similars.insert(tmp);
    }
}

void replace(string tolookup)
{
    int l = tolookup.length();
    string tmp = tolookup;
    for (int i = 0; i < l; i++)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            tmp[i] = c;
            if (dict[tmp])
                similars.insert(tmp);
        }
        tmp[i] = tolookup[i];
    }
}

void add(string tolookup)
{
    int l = tolookup.length();
    for (int i = 0; i <= l; i++)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            string tmp = tolookup;
            tmp.insert(tmp.begin() + i, c);
            if (dict[tmp])
                similars.insert(tmp);
        }
    }
}

void search(const string &tolookup)
{
    cout << tolookup;
    if (dict[tolookup])
        cout << " is correct";
    else
    {
        similars.clear();
        ans.clear();
        del_redundant(tolookup);
        replace(tolookup);
        add(tolookup);
        cout << ":";
        for (auto &item : similars)
            ans.push_back(item);
        sort(ans.begin(), ans.end(), cmp);
        for (auto &item : ans)
            cout << " " << item;
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    string tmp;
    int idx = 0;
    while (cin >> tmp && tmp != "#")
        dict[tmp] = ++idx;
    while (cin >> tmp && tmp != "#")
        search(tmp);
    return 0;
}