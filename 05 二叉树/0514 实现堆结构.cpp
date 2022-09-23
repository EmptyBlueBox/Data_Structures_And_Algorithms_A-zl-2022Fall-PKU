#include <iostream>
#include <set>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int N;
    cin >> N;
    while (N--)
    {
        multiset<int> a;
        int n;
        cin >> n;
        while (n--)
        {
            int order;
            cin >> order;
            if (order == 1)
            {
                int k;
                cin >> k;
                a.insert(k);
            }
            else
            {
                cout << *a.begin() << endl;
                a.erase(a.begin());
            }
        }
    }
}