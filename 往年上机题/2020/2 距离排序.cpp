#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct node
{
    int p[3];
} a[10];
struct node_pair
{
    int idx, idy;
    double dis;
    void get_dis()
    {
        int tmp = 0;
        for (int i = 0; i < 3; i++)
            tmp += (a[idx].p[i] - a[idy].p[i]) * (a[idx].p[i] - a[idy].p[i]);
        dis = sqrt(tmp);
    }
} pr[45];
bool cmp(const node_pair x, const node_pair y)
{
    return x.dis > y.dis;
}
int main()
{
    int n, pair_cnt = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 3; j++)
            cin >> a[i].p[j];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            pr[pair_cnt].idx = i, pr[pair_cnt].idy = j, pr[pair_cnt++].get_dis();
    stable_sort(pr, pr + pair_cnt, cmp);
    for (int i = 0; i < pair_cnt; i++)
        printf("(%d,%d,%d)-(%d,%d,%d)=%.2f\n", a[pr[i].idx].p[0], a[pr[i].idx].p[1], a[pr[i].idx].p[2], a[pr[i].idy].p[0], a[pr[i].idy].p[1], a[pr[i].idy].p[2], pr[i].dis);
}