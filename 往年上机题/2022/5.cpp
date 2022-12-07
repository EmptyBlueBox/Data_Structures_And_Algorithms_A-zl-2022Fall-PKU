#include <iostream>
using namespace std;
#define int long long

struct node
{
    int l = 0, r = 0, fa = 0;
    int nl = 0, nr = 0;
    bool is_lc = true;
} a[50010];
int bias = 0, ans;
void count_ini_bias(int x)
{
    bias += abs(a[x].nl - a[x].nr);
    if (a[x].l)
        count_ini_bias(a[x].l);
    if (a[x].r)
        count_ini_bias(a[x].r);
}
void cal_delta(int x, int up_delta)
{
    if (x == 0)
        return;
    if (a[x].l == 0 && a[x].r == 0)
    {
        ans = min(ans, bias + up_delta);
        return;
    }
    if (a[x].nl < a[x].nr)
        cal_delta(a[x].l, up_delta + 1), cal_delta(a[x].r, up_delta - 1);
    else if (a[x].nl > a[x].nr)
        cal_delta(a[x].l, up_delta - 1), cal_delta(a[x].r, up_delta + 1);
    else
        cal_delta(a[x].l, up_delta + 1), cal_delta(a[x].r, up_delta + 1);
}
int cal_num(int x)
{
    if (x == 0)
        return 0;
    a[x].nl = cal_num(a[x].l);
    a[x].nr = cal_num(a[x].r);
    return a[x].nl + a[x].nr + 1;
}
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int f, c;
        cin >> f >> c;
        a[c].fa = f;
        if (a[f].l == 0)
            a[f].l = c;
        else
            a[f].r = c, a[c].is_lc = false;
    }
    cal_num(1);
    count_ini_bias(1);
    ans = bias;
    cal_delta(1, 0);
    cout << ans << endl;
}