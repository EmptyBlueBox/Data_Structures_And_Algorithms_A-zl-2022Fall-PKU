#include <iostream>
#include <stack>
using namespace std;
//如果 s1，s2 是RBS，则 s2， {s1}s2，[s1]s2，(s1)s2 也是RBS，<s1>s2也是！！！
//每遇到一个右括号都要使得它与一个左括号匹配，用栈维护未匹配的左括号
int main()
{
    stack<char> s;
    int cnt = 0, x;
    char brkt[128];
    brkt['<'] = brkt['{'] = brkt['['] = brkt['('] = 'l';
    brkt['>'] = brkt['}'] = brkt[']'] = brkt[')'] = 'r';
    char pair[128];
    pair['>'] = '<', pair['}'] = '{', pair[']'] = '[', pair[')'] = '(';
    while ((x = getchar()) != '\n')
    {
        if (brkt[x] == 'l')
            s.push(x);
        else
        {
            if (s.empty())
            {
                cout << "Impossible\n";
                return 0;
            }
            cnt += pair[x] != s.top(), s.pop();
        }
    }
    if (!s.empty())
    {
        cout << "Impossible\n";
        return 0;
    }
    cout << cnt << endl;
}