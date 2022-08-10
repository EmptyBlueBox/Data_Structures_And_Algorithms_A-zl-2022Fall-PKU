#include <iostream>
#include <string>
using namespace std;

const int N = 1e6 + 1;
string a, b;
int nxt[N], nxtval[N], la, lb;
void GetNext()
{
    nxt[0] = nxtval[0] = -1;
    int i = 0, j = -1; //计算nxt数组将指针初始化为0和-1！！！
    while (i < lb)
        if (j == -1 || b[i] == b[j])
            nxt[++i] = ++j, nxtval[i] = j, nxtval[i] = (b[i] == b[j] ? nxtval[j] : nxtval[i]); //加上对nxt[i]的优化成为nxtval数组
        else
            j = nxt[j];
}
void KMP()
{
    int i = 0, j = 0;
    while (i < la)
    {
        if (j == -1 || a[i] == b[j]) //匹配了就增加指针
            i++, j++;
        else //不匹配就将模式串指针回溯，从而从模式串更靠前的位置开始匹配
            j = nxtval[j];
        if (j == lb)
            cout << i - lb + 1 << endl, j = nxtval[j]; //输出每一个匹配的字符串位置只用加上j = nxt[j]即可！！！
    }
}
int main()
{
    cin >> a >> b;
    la = a.length(), lb = b.length();
    GetNext();
    KMP();
    for (int i = 1; i <= lb; i++)
        cout << nxt[i] << ' '; //输出模式串前i个字母中最长的相同前后缀
}