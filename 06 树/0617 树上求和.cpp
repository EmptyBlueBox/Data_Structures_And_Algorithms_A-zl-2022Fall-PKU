/*
tricky tests:
0 () -> no
0 (0()()) -> yes
0 (0()(1()())) -> no
*/

#include <iostream>
using namespace std;

int goal;
bool flag;

inline char get_char_and_blank()
{
    char c;
    do
        c = getchar();
    while (c == ' ' || c == '\n' || c == '\t' || c == EOF);
    return c;
}

inline int readNumber()
{
    int res = 0;
    bool sgn = false;
    char c;
    do
    {
        c = getchar();
        if (c == '-')
            sgn = true;
    } while (c < '0' || c > '9');
    do
    {
        res = res * 10 + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    ungetc(c, stdin);
    return sgn ? -res : res;
}

bool isEmpty(int cur)
{
    char c;
    int t;

    c = get_char_and_blank(); //左括号
    c = get_char_and_blank(); //右括号或者数字
    if (c == ')')
        return true;

    ungetc(c, stdin);
    t = readNumber();
    int f1 = isEmpty(cur + t);
    int f2 = isEmpty(cur + t);
    if (f1 && f2 && cur + t == goal) //左右子树为NULL并且当前节点是最后一个节点
        flag = true;

    c = get_char_and_blank(); //读右括号
    return false;             //当前节点不是NULL节点
}

int main()
{
    while (~scanf("%d", &goal))
    {
        flag = 0;
        isEmpty(0);
        puts(flag ? "yes" : "no");
    }
}

/*非递归但是卡输入输出TLE*/
// #include <iostream>
// #include <stack>
// using namespace std;

// struct node
// {
//     int val, l = -1, r = -1, found_child = 0;
// } tree[50010]; //下标是节点的序号，用数组存树，指针递归MLE
// bool ok = false;
// void has_path_sum_n(int root, int n)
// {
//     if (ok)
//         return;
//     if (tree[root].l == -1 && tree[root].r == -1)
//         ok = (tree[root].val == n) || ok;
//     if (tree[root].r != -1)
//         has_path_sum_n(tree[root].r, n - tree[root].val);
//     if (tree[root].l != -1)
//         has_path_sum_n(tree[root].l, n - tree[root].val);
// }
// int main()
// {
//     ios::sync_with_stdio(false), cin.tie(0);
//     int n;
//     while (cin >> n)
//     {
//         ok = false;
//         int l = 0, r = 0;    //经过的括号个数
//         int node_sum = 0;    //经过的节点个数
//         stack<int> pre_node; //存的是节点的序号，不知道全部子节点的节点，也即DFS经过的节点，也包含叶子结点
//         while (true)         //构建树
//         {
//             char c = cin.peek();
//             if (c == ' ' || c == '\n')
//                 getchar();
//             else if (c == '(')
//                 getchar(), l++;
//             else if (c == ')')
//             {
//                 getchar();
//                 r++;
//                 if (!pre_node.empty()) //这个右括号对应的节点是一个pre_node中的BFS路径上的节点
//                 {
//                     int leaf_node = pre_node.top();       //作为DFS伸的最远的节点，可以看做叶子节点
//                     tree[leaf_node].found_child++;        //叶子节点的已探查子节点++
//                     if (tree[leaf_node].found_child == 2) //叶子节点已探查节点个数是2了，现在将这个叶子节点挂到它的父节点上，相当于BFS回溯
//                     {
//                         pre_node.pop(); //删除叶子节点
//                         if (!pre_node.empty())
//                         {
//                             if (tree[pre_node.top()].l == -1)
//                                 tree[pre_node.top()].l = leaf_node;
//                             else
//                                 tree[pre_node.top()].r = leaf_node;
//                         }
//                     }
//                 }
//                 if (l == r)
//                     break;
//             }
//             else //数字
//             {
//                 int val;
//                 cin >> val;
//                 tree[++node_sum].val = val;
//                 pre_node.push(node_sum);
//             }
//         }
//         has_path_sum_n(1, n);
//         cout << (ok && node_sum ? "yes\n" : "no\n"); // 0个节点恒不可以
//     }
// }

/*递归MLE*/
// #include <iostream>
// using namespace std;

// struct node
// {
//     int info;
//     node *l = NULL;
//     node *r = NULL;
// };
// void eat_empty()
// {
//     while (cin.peek() == ' ' || cin.peek() == '\n')
//         cin.get();
// }
// void build_tree(node *&x)
// {
//     cin.get();
//     eat_empty();
//     if (cin.peek() == ')') //特判空节点，不new节点直接返回
//     {
//         cin.get();
//         return;
//     }
//     x = new node;
//     cin >> x->info;
//     eat_empty();
//     build_tree(x->l);
//     eat_empty();
//     build_tree(x->r);
//     eat_empty();
//     cin.get(); //读取右括号
// }
// bool has_path_sum_n(node *x, int n)
// {
//     if (!x)
//         return false;
//     if(!x->l&&!x->r)
//         return x->info == n;
//     return has_path_sum_n(x->l, n - x->info) || has_path_sum_n(x->r, n - x->info);
// }
// int main()
// {
//     ios::sync_with_stdio(false), cin.tie(0);
//     int n;
//     while (cin >> n)
//     {
//         node *root = NULL;
//         eat_empty();
//         build_tree(root);
//         cout << (has_path_sum_n(root, n) && root ? "yes\n" : "no\n"); // root为NULL恒不可以
//     }
// }