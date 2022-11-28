#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int nxt_push = 1;
    stack<int> s;
    string ans; //用string存答案
    for (int i = 1; i <= n; i++)
    {
        int cur;
        cin >> cur;
        if (cur > n)
        {
            cout << "NO\n";
            return 0;
        }
        if (!s.empty() && s.top() == cur)
            ans += "POP " + to_string(cur) + '\n', s.pop();
        else if (cur < nxt_push)
        {
            cout << "NO\n";
            return 0;
        }
        else
        {
            while (nxt_push < cur)
                ans += "PUSH " + to_string(nxt_push) + '\n', s.push(nxt_push++);
            nxt_push++;
            ans += "PUSH " + to_string(cur) + '\n' + "POP " + to_string(cur) + '\n';
        }
    }
    cout << ans;
}