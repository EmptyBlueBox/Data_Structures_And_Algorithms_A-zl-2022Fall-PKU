#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

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