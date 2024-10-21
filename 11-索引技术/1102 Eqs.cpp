#include <iostream>
#include <unordered_map>
using namespace std;

int info[5], cube[101] = {0};
unordered_map<int, int> cnt;
int main()
{
    for (int i = 0; i < 5; i++)
        cin >> info[i];
    for (int i = -50; i <= 50; i++)
        cube[i + 50] = i * i * i;
    for (int i = -50; i <= 50; i++)
        if (i)
            for (int j = -50; j <= 50; j++)
                if (j)
                    cnt[-info[3] * cube[i + 50] - info[4] * cube[j + 50]]++;
    int ans = 0;
    for (int i = -50; i <= 50; i++)
        if (i)
            for (int j = -50; j <= 50; j++)
                if (j)
                    for (int k = -50; k <= 50; k++)
                        if (k)
                            ans += cnt[info[0] * cube[i + 50] + info[1] * cube[j + 50] + info[2] * cube[k + 50]];
    cout << ans << endl;
}