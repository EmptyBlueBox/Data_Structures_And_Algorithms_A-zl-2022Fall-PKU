#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            q.push(tmp);
        }
        int sum = 0;
        while (q.size() != 1)
        {
            int tmp = 0;
            tmp += q.top(), q.pop();
            tmp += q.top(), q.pop();
            sum += tmp;
            q.push(tmp);
        }
        cout << sum << endl;
    }
}