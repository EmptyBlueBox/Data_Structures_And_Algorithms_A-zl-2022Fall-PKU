#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <queue>
using namespace std;

int main()
{
    string goal;
    int n, k;
    cin >> goal >> n >> k;
    int line = cin.get() == '\n';

    string tmp;
    unordered_map<string, pair<int, set<int>>> dict;
    while (cin >> tmp)
        dict[tmp].first++, dict[tmp].second.insert(line), line += cin.get() == '\n';
    if (dict[goal].first)
        for (auto &i : dict[goal].second)
            cout << i << ' ';
    else //特判无此单词
        cout << -1;
    cout << endl;

    priority_queue<int> pq;
    for (auto &i : dict)
        pq.push(i.second.first);
    k--;
    while (k--)
        pq.pop();
    cout << pq.top() << endl;
}