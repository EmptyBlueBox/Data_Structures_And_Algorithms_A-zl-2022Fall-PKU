#include <iostream>
#include <vector>
#include <string>
using namespace std;

//字典树
struct node
{
    int cnt = 0; //几个单词经过这个节点
    node *ch[26] = {NULL};
};
node *root = new node; // root不算字母
vector<string> word;

void insert(string x)
{
    node *cur = root;
    int len = x.length();
    for (int i = 0; i < len; i++)
    {
        if (!cur->ch[x[i] - 'a'])
            cur->ch[x[i] - 'a'] = new node;
        cur->ch[x[i] - 'a']->cnt++;
        cur = cur->ch[x[i] - 'a'];
    }
}

string find_prefix(string x)
{
    node *cur = root;
    int len = x.length();
    string ans;
    for (int i = 0; i < len; i++)
    {
        if (cur->cnt == 1) // root的时候就加入了第一个字母，因此在遇到cnt==0时，对应的字母已经加入了
            return ans;
        ans += x[i];
        cur = cur->ch[x[i] - 'a'];
    }
    return x;
}

int main()
{
    string tmp;
    while (cin >> tmp)
        word.push_back(tmp), insert(tmp);
    for (auto i : word)
        cout << i << ' ' << find_prefix(i) << endl;
}