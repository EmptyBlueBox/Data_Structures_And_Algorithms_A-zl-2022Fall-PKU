#include <iostream>
using namespace std;

int main()
{
    char p, q;
    while (cin.get(p))
    {
        if (p == '/' && cin.peek() == '*')
        {
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
            while (cin.get(q) && p != q)
                if (q == '\\')
                    cout << q << char(cin.get());
                else
                    cout << q;
            cout << q;
        }
        else
            cout << p;
    }
}