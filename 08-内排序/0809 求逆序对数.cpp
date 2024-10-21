#include <iostream>
using namespace std;

int a[20001], tmp[20001], cnt = 0;
void merge_sort(int l, int r)
{
    if (l >= r) //不能是等于
        return;
    int mid = l + ((r - l) >> 1); //+-优先于位运算
    merge_sort(l, mid), merge_sort(mid + 1, r);
    int pl = l, pr = mid + 1, p = l;
    while (pl <= mid && pr <= r)
    {
        if (a[pl] <= a[pr])
            tmp[p++] = a[pl++];
        else
            tmp[p++] = a[pr++], cnt += mid - pl + 1; //右边指针指向的小，逆序对为左指针指向的和mid间的部分
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
        cnt = 0;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        merge_sort(0, n - 1);
        cout << cnt << endl;
    }
}