#include <string>
#include <iostream>
using namespace std;
#define endl '\n'

string tar, pat;
int nxt[1000001];
void get_next() // 计算next数组
{
    int i = 0, j = -1, len_pat = pat.length();
    nxt[0] = -1;
    while (i < len_pat) // 不是len-1，因为就是要计算nxt[len_pat]
        if (j == -1 || pat[i] == pat[j])
            nxt[++i] = ++j, nxt[i] = (pat[i] == pat[j] ? nxt[j] : nxt[i]); //加上对nxt[i]的优化成为nextval数组
        else
            j = nxt[j];
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    while (cin >> tar >> pat && tar != ".") //输入目标串tar和模式串pat
    {
        int len_pat = pat.length(), len_tar = tar.length();
        get_next();
        for (int i = 0; i < len_pat; i++)
            cout << nxt[i] << ' ';
        cout << endl;
        int i = 0, j = 0;
        while (i < len_tar && j < len_pat)
            if (j == -1 || tar[i] == pat[j])
                i++, j++;
            else
                j = nxt[j];
        cout << (j >= len_pat ? to_string(i - len_pat + 1) : "No Match") << endl; //输出目标串的第几个字符与模式串的第一个字符匹配
    }
}