#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    unordered_map<string, string> dict;
    string a, b;
    while (cin >> a >> b)
    {
        dict[b] = a;
        cin.ignore();
        if (cin.peek() == '\n')
            break;
    }
    while (cin >> a)
    {
        if (dict.find(a) != dict.end())
            cout << dict[a] << endl;
        else
            cout << "eh\n";
    }
}