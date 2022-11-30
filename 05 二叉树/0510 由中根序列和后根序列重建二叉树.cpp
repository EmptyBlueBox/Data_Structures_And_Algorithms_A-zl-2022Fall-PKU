#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int info;
    node *l = NULL;
    node *r = NULL;
};

vector<int> info;
int len;
void build_tree(node *root, int l1, int r1, int l2, int r2)
{
    int mid = info[r2];
    root->info = mid;
    for (int i = l1, a = 0, b = r1 - l1; i <= r1; i++, a++, b--) // a为左子树的节点数，b为右子树的节点数
        if (info[i] == mid)
        {
            if (a)
                root->l = new node, build_tree(root->l, l1, i - 1, l2, l2 + a - 1); //左子树至少一个节点
            if (b)
                root->r = new node, build_tree(root->r, i + 1, r1, r2 - b, r2 - 1); //右子树至少一个节点
        }
}

void pre(node *x)
{
    cout << x->info << ' ';
    if (x->l)
        pre(x->l);
    if (x->r)
        pre(x->r);
}

int main()
{
    int x;
    while (cin >> x)
        info.push_back(x);
    len = info.size() / 2;
    node *root = new node;
    build_tree(root, 0, len - 1, len, 2 * len - 1);
    pre(root);
}