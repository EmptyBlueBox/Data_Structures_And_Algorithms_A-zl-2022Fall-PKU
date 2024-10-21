#include <iostream>
#include <string>
#include <stack>
#include <cmath>
using namespace std;

bool is_integer(string a)
{
    return (a[0] == '-' && a.length() >= 2) || (a[0] >= '0' && a[0] <= '9');
}

int priority(char c)
{
    if (c == '(' || c == ')')
        return 4;
    else if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

stack<char> op;
stack<int> val;

void cal()
{
    int b = val.top();
    val.pop();
    int a = val.top();
    val.pop();
    char c = op.top();
    op.pop();
    if (c == '^')
        val.push(pow(a, b));
    else if (c == '*')
        val.push(a * b);
    else if (c == '/')
        val.push(a / b);
    else if (c == '+')
        val.push(a + b);
    else if (c == '-')
        val.push(a - b);
    return;
}

int eval(string a)
{
    a.append(" "); //最后一个数字后也要有一个空格
    while (!a.empty())
    {
        string tmp = a.substr(0, a.find(' '));
        a.erase(0, a.find(' ') + 1);
        if (is_integer(tmp))
            val.push(atoi(tmp.c_str()));
        else if (tmp[0] == '(')
            op.push('(');
        else if (tmp[0] == ')')
        {
            while (op.top() != '(')
                cal();
            op.pop(); //弹出左括号
        }
        else //把+前'('后的所有*和+都算出来，因为它们已经确定了计算的顺序了
        {
            while (!op.empty() && op.top() != '(' && priority(op.top()) >= priority(tmp[0]))
                cal();
            op.push(tmp[0]);
        }
    }
    while (!op.empty())
        cal();
    int ans = val.top();
    val.pop();
    return ans;
}

int main()
{
    int N;
    cin >> N, cin.ignore();
    string a;
    while (getline(cin, a))
        cout << eval(a) << endl;
}