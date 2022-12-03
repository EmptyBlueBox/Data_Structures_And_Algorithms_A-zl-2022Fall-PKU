#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<string, int> lib;
int f(string &a)
{
    int len = a.length(), ans = 0;
    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
            if (a[i] > a[j])
                ans++;
    return ans;
}

bool cmp(const string &a, const string &b)
{
    return lib[a] < lib[b];
}

int main()
{
    int n, l;
    cin >> l >> n;
    string a[100];
    for (int i = 0; i < n; i++)
        cin >> a[i], lib[a[i]] = f(a[i]);
    stable_sort(a, a + n, cmp);
    for (int i = 0; i < n; i++)
        cout << a[i] << endl;
}