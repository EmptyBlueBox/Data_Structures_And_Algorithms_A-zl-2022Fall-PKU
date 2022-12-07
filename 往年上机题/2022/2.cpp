#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
#define pii pair<int, int>
#define pipii pair<int, pair<int, int>>
#define ppiipii pair<pair<int, int>, pair<int, int>>

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    string a, b;
    unordered_map<string, string> dict;
    while (cin >> a >> b)
    {

        dict[b] = a;
        cin.ignore();
        if (cin.peek() == '\n')
            break;
    }
    while (cin >> a)
    {
        if (dict.find(a) == dict.end())
            cout << "eh\n";
        else
            cout << dict[a] << endl;
    }
}