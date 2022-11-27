#include <iostream>
#include <stack>
using namespace std;

//一层一层往上堆，如果某一层颜色内部出现了位于其下的颜色则说明最高这层至少涂了两次
int col[100010], s[100010] = {0}, e[100010];
stack<int> st; //栈顶是最后一次染的颜色
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> col[i];
        if (!s[col[i]])
            s[col[i]] = i;
        e[col[i]] = i;
    }
    col[n + 1] = 0, s[0] = 0, e[0] = n + 1;
    st.push(0); //假设最开始全部涂为无色
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == s[col[i]]) // i处的颜色是某个新颜色区间的起始位置
            st.push(col[i]), ans = max(ans, (int)st.size());
        if (col[i] != st.top()) //当前的颜色内部出现了位于其下的颜色
        {
            cout << -1 << endl;
            return 0;
        }
        if (i == e[col[i]])
            st.pop();
    }
    cout << ans - 1 << endl;
}