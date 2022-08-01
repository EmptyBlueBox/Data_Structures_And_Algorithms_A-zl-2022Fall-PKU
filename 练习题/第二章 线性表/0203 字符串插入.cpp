#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string str1, str2;
    while (cin >> str1 >> str2)
    {
        int pos = max_element(str1.begin(), str1.end()) - str1.begin(); // max_element函数返回最大元素的迭代器，可以用来求最大元素的下标
        str1.insert(pos + 1, str2);
        cout << str1 << endl;
    }
}