#include <iostream>
#include <string>
using namespace std;

string a;
int ans1 = -1, ans2 = -1, idx = 0, len;
void dfs(int d1, int d2) //一个函数对应树的一层
{
    ans1 = max(ans1, d1);
    ans2 = max(ans2, d2);
    int cnt = 0;
    while (idx < len)
        if (a[idx++] == 'd')                  //遇到d
            dfs(d1 + 1, d2 + cnt + 1), cnt++; //树深度加1，二叉树深度加已有的左子树个数加1
        else
            return; //离开当前层
}

int main()
{
    int cnt = 0;
    while (cin >> a && a != "#")
    {
        ans1 = -1, ans2 = -1, idx = 0, len = a.length();
        dfs(0, 0);
        printf("Tree %d: ", ++cnt);
        cout << ans1 << " => " << ans2 << endl; //左右有空格
    }
}