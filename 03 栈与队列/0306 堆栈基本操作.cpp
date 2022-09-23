#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
    int n, p = 1;
    cin >> n;
    stack<int> s;
    string ans;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (tmp < 1 || tmp > n || (!s.empty() && tmp < s.top()))
        {
            cout << "NO" << endl;
            return 0;
        }
        else if (!s.empty() && tmp == s.top())
            ans += "POP " + to_string(tmp) + "\n", s.pop();
        else
        {
            for (; p <= tmp; p++)
                ans += "PUSH " + to_string(p) + "\n", s.push(p);
            ans += "POP " + to_string(tmp) + "\n", s.pop();
        }
    }
    cout << ans;
}