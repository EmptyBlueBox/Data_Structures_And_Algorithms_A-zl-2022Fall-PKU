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

// #include <iostream>
// #include <algorithm>
// #include <cmath>
// #include <iomanip>
// using namespace std;

// struct point
// {
//     int id;
//     int x, y, z;
//     point() {}
//     point(int idd, int xx, int yy, int zz)
//     {
//         id = idd, x = xx, y = yy, z = zz;
//     }
//     friend ostream &operator<<(ostream &os, point &p)
//     {
//         os << '(' << p.x << ',' << p.y << ',' << p.z << ')';
//         return os;
//     }
//     friend istream &operator>>(istream &is, point &p)
//     {
//         is >> p.x >> p.y >> p.z;
//         return is;
//     }
// };
// struct p
// {
//     point a, b;
//     int dis; //实际距离的100倍
//     p() {}
//     p(point aa, point bb)
//     {
//         a = aa, b = bb;
//         dis = 0.5 + 100 * sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
//     }
//     friend ostream &operator<<(ostream &os, p &p)
//     {
//         os << p.a << '-' << p.b << '=' << fixed << setprecision(2) << p.dis / 100.0;
//         return os;
//     }
//     bool operator<(const p &other) const
//     {
//         if (dis != other.dis)
//             return dis > other.dis;
//         else if (a.id != other.a.id)
//             return a.id < other.a.id;
//         else
//             return b.id < other.b.id;
//     }
// };
// int main()
// {
//     int n;
//     point info[10];
//     cin >> n;
//     for (int i = 0; i < n; i++)
//         cin >> info[i], info[i].id = i;
//     p ans[101];
//     int cnt = 0;
//     for (int i = 0; i < n; i++)
//         for (int j = i + 1; j < n; j++)
//             ans[cnt++] = p(info[i], info[j]);
//     sort(ans, ans + cnt);
//     for (int i = 0; i < cnt; i++)
//         cout << ans[i] << endl;
// }