#include <iostream>
#include <string>
using namespace std;

string a;
int k, len, ans = 0, nxt[15001];
void f(int s)
{
    int i = s, j = s - 1;
    nxt[s] = s - 1;
    while (i < len)
        if (j == s - 1 || a[i] == a[j])
        {
            nxt[++i] = ++j;
            int tmp = j;
            while (tmp != s - 1)
                if (tmp - s >= k && 2 * (tmp - s) < i - s)
                {
                    ans++;
                    break;
                }
                else
                    tmp = nxt[tmp];
        }
        else
            j = nxt[j];
}
int main()
{
    cin >> a >> k;
    len = a.length();
    for (int i = 0; i < len; i++)
        f(i);
    cout << ans << endl;
}