#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node
{
    string s;
    Node *father;
    Node *left;
    Node *right;
};

Node *dfs(Node *root, string s)
{
    if (!root)
        return nullptr;
    if (root->s == s)
        return root->right;
    Node *ret;
    ret = dfs(root->left, s);
    if (ret != nullptr)
        return ret;
    ret = dfs(root->right, s);
    return ret;
}

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    while (t--)
    {
        Node *vr = nullptr;
        Node *cur = vr;
        string tmp, last;
        stack<Node *> s;
        bool inited = false;
        while (true)
        {
            last = tmp;
            getline(cin, tmp);
            int len = tmp.length();
            if (len == 0)
                break; // empty line
            if (!inited)
            {
                inited = true;
                vr = new Node{tmp, nullptr, nullptr, nullptr};
                cur = vr;
            }
            if (tmp[0] == '{')
                s.push(cur);
            else if (tmp[0] == '}')
            {
                cur = s.top();
                s.pop();
            }
            else
            {
                if (last == "{")
                {
                    cur->left = new Node{tmp, cur, nullptr, nullptr};
                    cur = cur->left;
                }
                else
                {
                    cur->right = new Node{tmp, cur, nullptr, nullptr};
                    cur = cur->right;
                }
            }
        }
        string toSearch;
        cin >> toSearch;
        Node *ret = dfs(vr, toSearch);
        if (ret)
        {
            while (ret)
            {
                cout << ret->s;
                ret = ret->right;
            }
            cout << '\n';
        }
        else
            cout << "No\n";
        cin.ignore(); // 自分
        getline(cin, tmp);
        getline(cin, tmp);
    }
}