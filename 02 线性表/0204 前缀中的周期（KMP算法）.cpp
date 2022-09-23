#include <iostream>
#include <string>
using namespace std;

int nxt[1000001] = {0};
int main()
{
    int len, N = 0;
    while (cin >> len && len)
    {
        cout << "Test case #" << ++N << endl;
        string a;
        cin >> a;
        int p = 1, prefix_len = 0; // prefix_len为当前共同前后缀的长度
        //计算next数组
        while (p < len) // next[p]
        {
            if (a[prefix_len] == a[p])
                nxt[p++] = ++prefix_len;
            else
            {
                if (prefix_len == 0)
                    nxt[p++] = 0;
                else
                    prefix_len = nxt[prefix_len - 1];
            }
        }
        for (int i = 2, rep = 2 - nxt[1]; i <= len; i++, rep = i - nxt[i - 1]) //利用next数组的共同前后缀性质得到重复子串
            if (rep != i && (i % rep == 0))
                cout << i << ' ' << i / rep << endl;
        cout << endl;
    }
}