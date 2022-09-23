#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct node
{
    char info;
    node *l = NULL;
    node *r = NULL;
};
void print_prefix(node *x)
{
    cout << x->info;
    if (x->l)
        print_prefix(x->l);
    if (x->r)
        print_prefix(x->r);
}
void print_suffix(node *x)
{
    if (x->l)
        print_suffix(x->l);
    if (x->r)
        print_suffix(x->r);
    cout << x->info;
}
void print_infix(node *x)
{
    if (x->l)
        print_infix(x->l);
    cout << x->info;
    if (x->r)
        print_infix(x->r);
}
int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        string tmp;
        node *father[101] = {NULL};   //上面最近的深i的节点指针,father[0]为root指针
        bool taken_up[101] = {false}; //记录*或者节点占据了左孩子
        while (cin >> tmp && tmp != "0")
        {
            int n = count(tmp.begin(), tmp.end(), '-');
            if (tmp.back() == '*')
                taken_up[n - 1] = true;
            else
            {
                node *add = new node;
                add->info = tmp.back();
                father[n] = add, taken_up[n] = false;
                if (n) //不是root
                {
                    if (taken_up[n - 1])
                        father[n - 1]->r = add;
                    else
                        father[n - 1]->l = add, taken_up[n - 1] = true;
                }
            }
        }
        print_prefix(father[0]), cout << endl;
        print_suffix(father[0]), cout << endl;
        print_infix(father[0]), cout << endl;
        cout << endl;
    }
}