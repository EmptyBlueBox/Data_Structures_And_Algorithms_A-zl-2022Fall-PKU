#include <iostream>
#include <queue>
using namespace std;

long long n, info[100001];
int main()
{
    cin >> n;
    for (long long i = 1; i <= n; i++)
        cin >> info[i];
    priority_queue<long long> l;
    priority_queue<long long, vector<long long>, greater<long long>> r;
    long long mid = info[1];
    cout << mid << endl;
    for (long long i = 2; i <= (n + 1) / 2; i++) //找每一个中位数
    {
        long long a = info[i * 2 - 2], b = info[i * 2 - 1];
        if ((mid - a) * (mid - b) <= 0)
            l.push(min(a, b)), r.push(max(a, b));
        else if (mid < a)
            l.push(mid), r.push(a), r.push(b), mid = r.top(), r.pop();
        else
            l.push(a), l.push(b), r.push(mid), mid = l.top(), l.pop();
        cout << mid << endl;
    }
}