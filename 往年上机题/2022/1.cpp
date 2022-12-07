#include <iostream>
using namespace std;

int nxt[100002];
int main()
{
    string a;
    cin >> a;
    int len = a.length();
    nxt[0] = -1;
    int i = 0, j = -1;
    while (i < len)
        if (j == -1 || a[i] == a[j])
            nxt[++i] = ++j;
        else
            j = nxt[j];
    int loop = len - nxt[len];
    if (loop != len && len % loop == 0)
        cout << 0 << endl;
    else
        cout << loop - nxt[len] % loop << endl;
}