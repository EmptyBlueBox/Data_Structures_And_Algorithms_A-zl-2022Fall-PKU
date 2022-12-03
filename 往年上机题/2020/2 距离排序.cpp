#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct point
{
    int x, y, z;
} pt[10];
struct node_pair
{
    int n1, n2;
    double dis;
    bool operator<(const node_pair &other) const //另一个结构体也要用const修饰
    {
        return dis > other.dis;
    }
} pr[100];
double f(int a, int b)
{
    return sqrt((pt[a].x - pt[b].x) * (pt[a].x - pt[b].x) + (pt[a].y - pt[b].y) * (pt[a].y - pt[b].y) + (pt[a].z - pt[b].z) * (pt[a].z - pt[b].z));
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> pt[i].x >> pt[i].y >> pt[i].z;
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            pr[cnt++] = node_pair{i, j, f(i, j)}; //可以用大括号直接初始化
    stable_sort(pr, pr + cnt);
    for (int i = 0; i < cnt; i++)
    {
        point a = pt[pr[i].n1], b = pt[pr[i].n2];
        printf("(%d,%d,%d)-(%d,%d,%d)=%.2f\n", a.x, a.y, a.z, b.x, b.y, b.z, pr[i].dis);
    }
}