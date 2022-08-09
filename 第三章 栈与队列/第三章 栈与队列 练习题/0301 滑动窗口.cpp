#include <iostream>
#include <deque>
using namespace std;

int info[1000001] = {0};
deque<int> dq;
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> info[i];
    for (int i = 1; i <= n; i++)
    {
        while (!dq.empty() && i - dq.front() >= k)
            dq.pop_front();
        while (!dq.empty() && info[dq.back()] >= info[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k)
            cout << info[dq.front()] << ' ';
    }
    cout << endl;
    dq.clear();
    for (int i = 1; i <= n; i++)
    {
        while (!dq.empty() && i - dq.front() >= k)
            dq.pop_front();
        while (!dq.empty() && info[dq.back()] <= info[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k)
            cout << info[dq.front()] << ' ';
    }
}