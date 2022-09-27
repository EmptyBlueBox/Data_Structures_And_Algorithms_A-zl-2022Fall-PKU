#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct node
{
    node *l = NULL;
    node *r = NULL;
};
int get_height(node *x)
{
    if (!x)
        return 0;
    else
        return max(get_height(x->l), get_height(x->r)) + 1;
}
int main()
{
    string a;
    int N = 0;
    while (cin >> a && a != "#")
    {
        int h1 = 0, h2 = 0, len = a.length();
        for (int i = 0, h_now = 0; i < len; i++)
            h_now += (a[i] == 'd' ? 1 : -1), h1 = max(h1, h_now);
        node *root = new node;
        node *cur = root;
        stack<node *> pre_root; //在树上的上一层的父节点和同一层的上一个节点
        for (int i = 0; i < len; i++)
            if (a[i] == 'd') //走到树的下一层
            {
                if (!i || a[i - 1] == 'd') //下一层再下一层
                    pre_root.push(cur), cur->l = new node, cur = cur->l;
                else //上一层再下一层
                    cur->r = new node, cur = cur->r;
            }
            else if (!pre_root.empty() && a[i - 1] == 'u')
                cur = pre_root.top(), pre_root.pop();
        h2 = get_height(root);
        printf("Tree %d: %d => %d\n", ++N, h1, h2 - 1);
    }
}