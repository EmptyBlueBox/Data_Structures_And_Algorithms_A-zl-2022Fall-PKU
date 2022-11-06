// SPFA判环，queue存将要松弛的节点，使用vector模拟邻接表
// 通过松弛维护一个最短路径（最多钱数）数组
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct edge
{
    int to;
    double ex_rate, commission;
};
vector<edge> e[101]; //邻接表
//找最小路返回是否有负环，找最大路返回是否有正环（如本题）
bool SPFA(int s, double v) // v的类型不是int！！！
{
    queue<int> q;
    q.push(s);
    bool in_queue[101] = {false}; //在队列中就不入队列
    in_queue[s] = true;
    //如果某个节点入队了n次，说明有正环，但是不一定回到源点。回到源点的判断比较简单，只需判断max_money[s]是否变大即可
    // int vis_num[101]={0};
    // vis_num[s] = 1;
    double max_money[101] = {0}; //对每一种钱，现在得到的最多钱数
    max_money[s] = v;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        in_queue[now] = false; //将出队标记置0
        for (auto i : e[now])  //用now节点的出边维护周围一圈钱种类的最多钱数
        {
            if (max_money[i.to] < (max_money[now] - i.commission) * i.ex_rate)
            {
                max_money[i.to] = (max_money[now] - i.commission) * i.ex_rate;
                if (!in_queue[i.to])
                    q.push(i.to), in_queue[i.to] = true; //不在队列中就入队列
            }
        }
        if (max_money[s] > v) //源点钱可能增加
            return true;
    }
    return false;
}
int main()
{
    int currency_num, ex_point_num, money_type;
    double money_num;
    cin >> currency_num >> ex_point_num >> money_type >> money_num;
    for (int i = 0; i < ex_point_num; i++)
    {
        int t1, t2;
        double r1, c1, r2, c2;
        cin >> t1 >> t2 >> r1 >> c1 >> r2 >> c2;
        e[t1].push_back({t2, r1, c1});
        e[t2].push_back({t1, r2, c2});
    }
    cout << (SPFA(money_type, money_num) ? "YES\n" : "NO\n");
}