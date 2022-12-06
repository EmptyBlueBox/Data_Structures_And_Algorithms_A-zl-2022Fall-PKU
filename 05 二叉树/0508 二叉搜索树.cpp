#include <iostream>
using namespace std;

struct node
{
    int info;
    node *l = NULL;
    node *r = NULL;
};
node *root = new node;

void insert(int x)
{
    if (x == root->info) //无重复节点
        return;
    node *cur = root;
    node *nxt = x > cur->info ? cur->r : cur->l;
    while (nxt)
        if (x == nxt->info) //无重复节点
            return;
        else
            cur = nxt, nxt = (x > nxt->info ? nxt->r : nxt->l);
    if (x > cur->info)
        cur->r = new node, cur->r->info = x;
    else
        cur->l = new node, cur->l->info = x;
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
    cin >> root->info;
    int tmp;
    while (cin >> tmp)
        insert(tmp);
    pre(root);
    cout << endl;
}