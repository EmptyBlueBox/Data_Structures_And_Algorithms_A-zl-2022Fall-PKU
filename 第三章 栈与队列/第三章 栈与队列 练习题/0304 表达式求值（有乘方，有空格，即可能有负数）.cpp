#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

stack<char> op;
stack<int> ans;
int priority(char op)
{
    if (op == '(' || op == ')')
        return 4;
    else if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}
void calculate(char op)
{
    int y = ans.top();
    ans.pop();
    int x = ans.top();
    ans.pop();
    switch (op)
    {
    case '+':
        ans.push(x + y);
        break;
    case '-':
        ans.push(x - y);
        break;
    case '*':
        ans.push(x * y);
        break;
    case '/':
        ans.push(x / y);
        break;
    case '^':
        ans.push(pow(x, y));
        break;
    }
}
int main()
{
    int N, len;
    cin >> N, cin.ignore();
    while (N--)
    {
        string f, tmp;   //有空格分割的使用字符串函数，因为有可能出现负数
        getline(cin, f); // cin和get不消除\n，而getline消除\n！！！
        len = f.length();
        while (!f.empty())
        {
            tmp = f.substr(0, f.find(' '));
            f.erase(0, tmp.length() + 1); // string::find(int pos, int len)不到就返回-1而不是string::end()!!!
            if ((tmp[0] >= '0' && tmp[0] <= '9') || (tmp[0] == '-' && tmp.length() > 1))
                ans.push(atoi(tmp.c_str()));
            else if (tmp[0] == ')')
            {
                while (op.top() != '(')
                    calculate(op.top()), op.pop();
                op.pop();
            }
            else if (op.empty() || op.top() == '(' || priority(tmp[0]) > priority(op.top()))
                op.push(tmp[0]);
            else
                calculate(op.top()), op.pop(), f.insert(0, tmp + ' '); //回溯一次，从而使下一次循环仍然比较当前的运算符
        }
        while (!op.empty())
            calculate(op.top()), op.pop();
        cout << ans.top() << endl;
        ans.pop();
    }
}