#include <iostream>
#include <stack>
#include <deque>
using namespace std;

stack<char> op;
stack<int> ans;
int priority(char op) //要使括号优先级最高！！！
{
    if (op == '(' || op == ')')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}
void calculate(char op) //对后缀表达式每一个运算符进行计算
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
    }
}
int main()
{
    int N, len;
    cin >> N;
    while (N--)
    {
        string f;
        cin >> f;
        len = f.length();
        for (int i = 0; i < len; i++)
        {
            if (f[i] < '0' || f[i] > '9') //表达式遇到符号
                //遇到右括号就计算所有括号内的运算符
                if (f[i] == ')')
                {
                    while (op.top() != '(')
                        calculate(op.top()), op.pop();
                    op.pop(); //删除左括号
                }
                // 1.待定符号栈为空 2.这个符号是某个括号内的唯一运算符 3.当前运算符应该更早算（即当前运算符优先级更高，包含括号的优先级！！！）就直接压栈
                else if (op.empty() || op.top() == '(' || priority(f[i]) > priority(op.top()))
                    op.push(f[i]);
                //计算op栈内的一个符号
                else
                    calculate(op.top()), op.pop(), i--; //回溯一次i，从而使下一次循环仍然比较当前的运算符
            else
            {
                string tmp;
                while (f[i] >= '0' && f[i] <= '9')
                    tmp += f[i], i++;
                i--; //回溯一次i，从而使下一次循环仍然比较下一个的运算符
                ans.push(atoi(tmp.c_str()));
            }
        }
        while (!op.empty())
            calculate(op.top()), op.pop();
        cout << ans.top() << endl;
        ans.pop();
    }
}