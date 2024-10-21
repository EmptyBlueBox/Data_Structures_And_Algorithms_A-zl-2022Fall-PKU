#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    map<string, set<string>> lib;
    string tmp;
    while (cin >> tmp && tmp != "XXXXXX")
    {
        string key = tmp;
        sort(key.begin(), key.end());
        lib[key].insert(tmp);
    }
    while (cin >> tmp && tmp != "XXXXXX")
    {
        string key = tmp;
        sort(key.begin(), key.end());
        if (lib[key].empty())
            cout << "NOT A VALID WORD\n******\n";
        else
        {
            for (auto &i : lib[key])
                cout << i << endl;
            cout << "******\n";
        }
    }
}