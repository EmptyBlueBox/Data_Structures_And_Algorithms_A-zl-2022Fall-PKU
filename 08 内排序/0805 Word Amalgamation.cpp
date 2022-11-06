#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    vector<string> lib;
    vector<int> cnt[26];
    string tmp;
    while (cin >> tmp && tmp != "XXXXXX")
    {
        lib.push_back(tmp);
        for (int i = 'a'; i <= 'z'; i++)
            cnt[i - 'a'].push_back(count(tmp.begin(), tmp.end(), i));
    }
    int n = lib.size();
    while (cin >> tmp && tmp != "XXXXXX")
    {
        int unordered_word[26];
        for (int i = 'a'; i <= 'z'; i++)
            unordered_word[i - 'a'] = count(tmp.begin(), tmp.end(), i);
        set<string> ans;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 26; j++)
                if (cnt[j][i] != unordered_word[j])
                    goto nxt_word;
            ans.insert(lib[i]);
        nxt_word:;
        }
        if (ans.empty())
        {
            cout << "NOT A VALID WORD\n******\n";
            continue;
        }
        while (!ans.empty())
        {
            cout << *ans.begin() << endl;
            ans.erase(ans.begin());
        }
        cout << "******\n";
    }
}