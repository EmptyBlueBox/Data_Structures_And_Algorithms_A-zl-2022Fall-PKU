#include <iostream>
#include <queue>
#include <set>
using namespace std;

int main()
{
    int n, m, p; // n张卡，m个人，洗一次牌切p张
    cin >> m >> n >> p;
    queue<int> q;
    set<int> ans;
    for (int i = 1; i <= n; i++)
        q.push(i);
    for (int i = 1; i <= n / m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j == m)
                ans.insert(q.front());
            q.pop();
            for (int k = 1; k <= p; k++)
                q.push(q.front()), q.pop();
        }
    }
    for (auto i : ans)
        cout << i << endl;
}