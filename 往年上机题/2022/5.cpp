#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cstring>
#include <cctype>
#define LIM 500
using namespace std;
unordered_map<char, int> symtab;
char exprTree[LIM][LIM];

struct Node
{
    char symbol;
    Node *left, *right;
};
unordered_map<Node *, bool> isLeaf;

inline int get_depth(Node *root)
{
    if (!root)
        return 0;
    return max(get_depth(root->left), get_depth(root->right)) + 1;
}

inline string infix_to_suffix(const string &str)
{
    string ret;
    stack<char> s;
    for (auto &&c : str)
    {
        if (isalpha(c))
        {
            ret += c;
        }
        else if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            while (s.top() != '(')
            {
                ret += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (c == '+' || c == '-')
        {
            while (!s.empty() && s.top() != '(')
            {
                ret += s.top();
                s.pop();
            }
            s.push(c);
        }
        else
        { // * or /
            while (!s.empty() && (s.top() == '*' || s.top() == '/'))
            {
                ret += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty())
    {
        ret += s.top();
        s.pop();
    }
    return ret;
}

int calc(Node *root)
{
    switch (root->symbol)
    {
    case '+':
        return calc(root->left) + calc(root->right);
    case '-':
        return calc(root->left) - calc(root->right);
    case '*':
        return calc(root->left) * calc(root->right);
    case '/':
        return calc(root->left) / calc(root->right);
    default:
        return symtab[root->symbol];
    }
}

void print_exprTree(Node *root, int x, int y, int span)
{
    if (!root)
        return;
    exprTree[x][y - 1] = root->symbol;
    if (root->left)
    {
        exprTree[x + 1][y - 2] = '/';
        print_exprTree(root->left, x + 2, y - span, span >> 1);
    }
    if (root->right)
    {
        exprTree[x + 1][y] = '\\';
        print_exprTree(root->right, x + 2, y + span, span >> 1);
    }
}

int main()
{
    string infix;
    int n;
    cin >> infix >> n;
    for (int i = 0; i < n; i++)
    {
        char var;
        int val;
        cin >> var >> val;
        symtab[var] = val;
    }
    string suffix = infix_to_suffix(infix);
    cout << suffix << endl;
    Node *root = nullptr;
    stack<Node *> s;
    for (auto &c : suffix)
    {
        root = new Node{c, nullptr, nullptr};
        if (!isalpha(c))
        {
            root->right = s.top();
            s.pop();
            root->left = s.top();
            s.pop();
        }
        s.push(root);
    }
    int d = get_depth(root);
    memset(exprTree, ' ', sizeof(exprTree));
    print_exprTree(root, 0, 1 << (d - 1), 1 << (d - 2));
    int lineCnt = 0;
    for (int i = 0; i < LIM; i++)
    {
        int j = LIM - 1;
        while (j >= 0 && exprTree[i][j] == ' ')
            j--;
        if (j > -1)
        { // if this line is not empty
            lineCnt++;
            exprTree[i][j + 1] = '\0';
        }
        else
            break;
    }
    for (int i = 0; i < lineCnt; i++)
    {
        cout << exprTree[i] << endl;
    }
    cout << calc(root) << endl;
}