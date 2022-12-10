#include <iostream>
using namespace std;

int a[20001], ans = 0, tmp[20001];
void merge_sort(int l, int r)
{
    if (l >= r)
        return;
    int mid = l + ((r - l) >> 1);
    merge_sort(l, mid), merge_sort(mid + 1, r);
    int pl = l, pr = mid + 1, p = l;
    while (pl <= mid && pr <= r)
    {
        if (a[pl] <= a[pr])
            tmp[p++] = a[pl++];
        else
            tmp[p++] = a[pr++], ans += mid - pl + 1;
    }
    while (pl <= mid)
        tmp[p++] = a[pl++];
    while (pr <= r)
        tmp[p++] = a[pr++];
    for (int i = l; i <= r; i++)
        a[i] = tmp[i];
}
int main()
{
    int n;
    while (cin >> n && n)
    {
        ans = 0;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        merge_sort(0, n - 1);
        cout << ans << endl;
    }
}