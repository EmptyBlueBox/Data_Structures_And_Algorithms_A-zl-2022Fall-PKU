#include <iostream>
#include <vector>
#include <string>
using namespace std;

//字典树
struct node
{
    node *ch[10] = {NULL};
    int cnt = 0;
    bool is_end = false; //存是否是最后一个字符
};

//有互相为前缀的两个字符串
bool has_contradict_prefix = false;

void insert(node *root, string a)
{
    int len = a.length();
    node *cur = root;
    for (int i = 0; i < len; i++)
    {
        if (!cur->ch[a[i] - '0'])
            cur->ch[a[i] - '0'] = new node;
        cur = cur->ch[a[i] - '0'];
        cur->cnt++;
    }
    cur->is_end = true;
}

//中序遍历树，看每一个节点是不是前缀节点
void traversal(node *root)
{
    if (has_contradict_prefix)
        return;
    if (root->is_end && root->cnt >= 2)
    {
        has_contradict_prefix = true;
        return;
    }
    for (int i = 0; i < 10; i++)
        if (root->ch[i])
            traversal(root->ch[i]);
}

//后序遍历销毁动态分配的子节点
void destroy_tree(node *root)
{
    for (int i = 0; i < 10; i++)
        if (root->ch[i])
            destroy_tree(root->ch[i]);
    delete root;
    root = NULL;
}

#ifdef SAVE_EVERY_String

//是另外某个字符串的前缀
bool is_prefix(node *root, string a)
{
    int len = a.length();
    node *cur = root;
    for (int i = 0; i < len; i++)
        cur = cur->ch[a[i] - '0'];
    return cur->cnt != 1;
}

#endif

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        node *root = new node;
        has_contradict_prefix = false;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string a;
            cin >> a;
            insert(root, a);
        }
        traversal(root);
        cout << (has_contradict_prefix ? "NO\n" : "YES\n");
        destroy_tree(root);

#ifdef SAVE_EVERY_String

        for (int i = 0; i < n; i++)
            if (is_prefix(root, a[i]))
            {
                cout << "NO\n";
                goto loop;
            }
        cout << "YES\n";
    loop:;

#endif
    }
}