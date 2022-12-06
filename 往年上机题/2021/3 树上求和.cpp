#include <iostream>
using namespace std;

char get_b_c()
{
    char c = getchar();
    while (c == ' ' || c == '\t' || c == '\n')
        c = getchar();
    return c;
}

int get_i()
{
    char c = getchar();
    int op;
    if (c == '-')
        op = -1;
    else
        op = 1, ungetc(c, stdin);

    int ans = 0;
    c = getchar();
    while (c >= '0' && c <= '9')
        ans = 10 * ans + c - '0', c = getchar();

    ungetc(c, stdin);
    return ans * op;
}

int target;
bool has_path = false; //即使为true也不要直接返回
bool empty(int sum)
{
    get_b_c();
    char c = get_b_c();
    if (c == ')')
        return true;
    else
        ungetc(c, stdin);

    int cur = get_i();
    bool l_empty = empty(sum + cur);
    bool r_empty = empty(sum + cur);
    if (l_empty && r_empty && sum + cur == target)
        has_path = true;

    get_b_c();
    return false;
}

int main()
{
    while (~scanf("%d", &target))
    {
        has_path = false;
        empty(0);
        puts(has_path ? "yes" : "no");
    }
}