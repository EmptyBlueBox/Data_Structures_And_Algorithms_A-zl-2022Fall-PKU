#include <iostream>
#include <unordered_set>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        unordered_set<int> s;
        while (n--)
        {
            int tmp;
            cin >> tmp;
            if (s.find(tmp) != s.end())
                continue;
            cout << tmp << ' ';
            s.insert(tmp);
        }
        cout << endl;
    }
}