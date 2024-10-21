#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    string all[100];
    queue<string> num[9], alg[4];
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> all[i];
        num[all[i][1] - '1'].push(all[i]);
    }
    for (int i = 0; i < 9; i++)
    {
        printf("Queue%d:", i + 1);
        while (!num[i].empty())
            cout << num[i].front() << ' ', alg[num[i].front()[0] - 'A'].push(num[i].front()), num[i].pop();
        cout << endl;
    }
    for (int i = 0; i < 4; i++)
    {
        printf("Queue%c:", i + 'A');
        while (!alg[i].empty())
            cout << alg[i].front() << ' ', alg[i].pop();
        cout << endl;
    }
    sort(all, all + N);
    for (int i = 0; i < N; i++)
        cout << all[i] << ' ';
}