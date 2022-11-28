#include <iostream>
#include <string>
using namespace std;

const int N = 1e3 + 1;

void GetNext(int *nxt, int *nxtval, string b)
{
    nxt[0] = nxtval[0] = -1;
    int lb = b.length();
    int i = 0, j = -1; //计算nxt数组将指针初始化为0和-1！！！
    while (i < lb)
        if (j == -1 || b[i] == b[j])
            nxt[++i] = ++j, nxtval[i] = j, nxtval[i] = (b[i] == b[j] ? nxtval[j] : nxtval[i]); //加上对nxt[i]的优化成为nxtval数组
        else
            j = nxt[j];
    cout << "最长相同前后缀长度 ：";
    for (int i = 1; i <= lb; i++)
        cout << nxt[i] << ' '; //输出模式串前i个字母中最长的相同前后缀
    cout << endl;
}

void KMP(int *nxt, string a, string b)
{
    int la = a.length(), lb = b.length();
    int i = 0, j = 0, match_cnt = 0;
    while (i < la)
    {
        if (j == -1 || a[i] == b[j]) //匹配了就增加指针
            i++, j++;
        else //不匹配就将模式串指针回溯，从而从模式串更靠前的位置开始匹配
            j = nxt[j];
        if (j == lb)
            cout << "第" << ++match_cnt << "次匹配索引"
                 << "：" << i - lb << endl,
                j = nxt[j]; //输出每一个匹配的字符串位置只用加上j = nxt[j]即可！！！
    }
}

int main()
{
    string a, b;
    while (cin >> a >> b)
    {
        int nxt[N], nxtval[N];
        GetNext(nxt, nxtval, b);
        KMP(nxtval, a, b);
    }
}