#include <iostream>
#include <set>
using namespace std;

int main()
{
    int N;
    while (cin >> N && N)
    {
        set<pair<int, int>> s;
        pair<int, int> tmp;
        while (N--)
            cin >> tmp.first >> tmp.second, s.insert(tmp);
        int ans = 0;
        for (auto &i : s)
            for (auto &j : s)
                if (i < j)
                {
                    int dx = j.first - i.first, dy = j.second - i.second;
                    pair<int, int> ii(i.first + dy, i.second - dx), jj(j.first + dy, j.second - dx);
                    if (s.find(ii) != s.end() && s.find(jj) != s.end())
                        ans++;
                }
        cout << ans / 2 << endl;
    }
}