#include <iostream>
using namespace std;

int nxt[1000010] = {0};
string a;
void Get_Next()
{
    int i = 0, j = -1, l = a.length();
    nxt[0] = -1;
    while (i < l)
        if (j == -1 || a[i] == a[j])
            nxt[++i] = ++j;
        else
            j = nxt[j];
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    while (cin >> a && a != ".")
    {
        Get_Next();
        int len = a.length(), rep = len - nxt[len];
        cout << (len % rep ? 1 : len / rep) << endl;
    }
}