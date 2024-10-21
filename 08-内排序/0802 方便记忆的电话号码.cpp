#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    int n, replacement[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
    cin >> n;
    map<string, int> a;
    string tmp;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        while (tmp.find('-') != string::npos)       //查找不到不是string::end()
            tmp.erase(tmp.begin() + tmp.find('-')); // string::find()返回下标，string::erase(string::iterator _itr)不是下标
        for (int i = 0; i < tmp.length(); i++)
            if (tmp[i] >= 'A' && tmp[i] <= 'Z')
                tmp[i] = replacement[tmp[i] - 'A'] + '0';
        tmp.insert(tmp.begin() + 3, '-');
        a[tmp]++;
    }
    bool out_put = false;
    for (auto i : a)
        if (i.second - 1)
            out_put = true, cout << i.first << ' ' << i.second << endl;
    if (!out_put)
        cout << "No duplicates." << endl;
}