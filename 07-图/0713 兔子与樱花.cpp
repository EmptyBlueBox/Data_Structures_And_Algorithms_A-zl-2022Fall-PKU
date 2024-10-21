#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;
#define pii pair<int, int>
#define pipii pair<int, pair<int, int>>
#define ppiipii pair<pair<int, int>, pair<int, int>>

int main()
{
    unordered_map<int, string> name;
    unordered_map<string, int> id;
    int n;
    cin >> n;
    while (n--)
    {
        string tmp;
        cin >> tmp;
        name[n] = tmp, id[tmp] = n;
    }

    vector<pii> edge[30];
    cin >> n;
    while (n--)
    {
        string n1, n2;
        int w;
        cin >> n1 >> n2 >> w;
        edge[id[n1]].push_back({w, id[n2]});
        edge[id[n2]].push_back({w, id[n1]});
    }

    cin >> n;
    while (n--)
    {
        string s, e;
        cin >> s >> e;
        int sp = id[s], ep = id[e];

        priority_queue<ppiipii, vector<ppiipii>, greater<ppiipii>> q; //距离源的距离，与上一个节点的距离，上一个节点，这一个节点
        for (auto &sp_side : edge[sp])                                //把源点周围的所有点放进队列，相当于已经知道了源点距离源点的距离
            q.push({{sp_side.first, sp_side.first}, {sp, sp_side.second}});

        int dis[30];
        memset(dis, 0x3f, sizeof(dis));
        dis[sp] = 0;

        string path[30];
        path[sp] = s;

        while (!q.empty())
        {
            int w_all = q.top().first.first, w_one = q.top().first.second, pre = q.top().second.first, cur = q.top().second.second;
            q.pop(); //拿出所有信息一定pop

            if (dis[cur] != 0x3f3f3f3f)
                continue;
            else
                dis[cur] = w_all, path[cur] = path[pre] + "->(" + to_string(w_one) + ")->" + name[cur];

            if (dis[ep] != 0x3f3f3f3f) //找到答案
            {
                cout << path[ep] << endl;
                break;
            }
            for (auto &cur_side : edge[cur])
                if (dis[cur_side.second] == 0x3f3f3f3f)
                    q.push({{w_all + cur_side.first, cur_side.first}, {cur, cur_side.second}});
        }
    }
}