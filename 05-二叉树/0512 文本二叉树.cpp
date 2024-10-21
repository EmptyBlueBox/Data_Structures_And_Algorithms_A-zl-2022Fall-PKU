#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct node
{
    node *l = NULL;
    node *r = NULL;
    bool has_left = true;
    char info;
};

void pre(node *x)
{
    cout << x->info;
    if (x->l)
        pre(x->l);
    if (x->r)
        pre(x->r);
}

void in(node *x)
{
    if (x->l)
        in(x->l);
    cout << x->info;
    if (x->r)
        in(x->r);
}

void suf(node *x)
{
    if (x->l)
        suf(x->l);
    if (x->r)
        suf(x->r);
    cout << x->info;
}

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        node *root = new node;
        cin >> root->info;

        node *a[101]; //最近的有i个'-'的祖先节点
        a[0] = root;

        string cur;
        while (cin >> cur && cur != "0")
        {
            int depth = count(cur.begin(), cur.end(), '-');
            if (cur.back() == '*')
                a[depth - 1]->has_left = false;
            else if (a[depth - 1]->has_left && !a[depth - 1]->l) //父节点有左子节点且没有放左子节点那就放进去
                a[depth - 1]->l = new node, a[depth] = a[depth - 1]->l, a[depth]->info = cur.back();
            else
                a[depth - 1]->r = new node, a[depth] = a[depth - 1]->r, a[depth]->info = cur.back();
        }
        pre(root);
        cout << endl;
        suf(root);
        cout << endl;
        in(root);
        cout << "\n\n";
    }
}