#include <iostream>
using namespace std;

//注释里的字符串是注释
//字符串里的注释是字符串
//注释和字符串互不影响
//转义字符只会影响字符串中右引号的位置
int main()
{
    char p, q;
    while (cin.get(p))
    {
        if (p == '/' && cin.peek() == '*')
        {
            cin.get();
            while (cin.get(p))
                if (p == '*' && cin.peek() == '/')
                {
                    cin.get();
                    break;
                }
        }
        else if (p == '\'' || p == '"')
        {
            cout << p;
            while (cin.get(q))
                if (q == '\\')
                    cout << q << (char)cin.get(); //一定要把cin.get()变成字符，否则输出数字
                else if (q == p)
                {
                    cout << q;
                    break;
                }
                else
                    cout << q;
        }
        else
            cout << p;
    }
}