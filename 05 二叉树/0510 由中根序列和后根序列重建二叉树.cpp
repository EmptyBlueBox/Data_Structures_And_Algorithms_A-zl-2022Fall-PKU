#include <iostream>
#include <vector>
using namespace std;
#define infix info
#define suffix (&info[len])
struct node
{
    int info;
    node *l;
    node *r;
};
vector<int> info;
int len;
void get_tree(node *&root, int l1, int l2, int r1, int r2) //构建节点root，root要传引用
{
    if (l1 > l2 || r1 > r2)
        return;
    root = new node{suffix[r2], NULL, NULL};
    int loc_r2;
    for (loc_r2 = l1; loc_r2 <= l2; loc_r2++)
        if (infix[loc_r2] == suffix[r2])
            break;
    get_tree(root->l, l1, loc_r2 - 1, r1, r1 + loc_r2 - l1 - 1);
    get_tree(root->r, loc_r2 + 1, l2, r1 + loc_r2 - l1, r2 - 1);
}
void print_prefix(node *x)
{
    cout << x->info << ' ';
    if (x->l)
        print_prefix(x->l);
    if (x->r)
        print_prefix(x->r);
}
int main()
{
    int tmp;
    while (cin >> tmp)
        info.push_back(tmp);
    len = info.size() / 2;
    node *root = NULL;
    get_tree(root, 0, len - 1, 0, len - 1);
    print_prefix(root);
}