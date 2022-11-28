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
            cin.get(); //吃掉 *
            while (cin.get(p))
                if (p == '*' && cin.peek() == '/')
                {
                    cin.get(); //吃掉 / !!!
                    break;
                }
        }
        else if (p == '\'' || p == '"')
        {
            cout << p;                            //输出左引号
            while (cin.get(q) && p != q)          //出现右引号之前一直输出原样的字符
                if (q == '\\')                    //出现转义字符，下一个字符一定是字符串的一部分，直接输出下一个字符
                    cout << q << char(cin.get()); //一定要把cin.get()变成字符，否则输出数字
                else
                    cout << q;
            cout << q; //输出右引号
        }
        else
            cout << p;
    }
}