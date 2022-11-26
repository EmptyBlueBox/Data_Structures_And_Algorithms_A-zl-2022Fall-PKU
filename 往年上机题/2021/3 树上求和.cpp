#include <iostream>
using namespace std;

bool has_path = false;
int goal;

//读取一段可能的空白与这之后的一个字符
char get_blank_and_char()
{
    char c;
    do
        c = getchar();
    while (c == ' ' || c == '\t' || c == '\n');
    return c;
}

//默认前面没有空白
int get_integer()
{
    int positive;
    char c;
    //处理负号
    c = getchar();
    positive = (c == '-' ? 0 : 1);
    if (c != '-') //不是负号放回去
        ungetc(c, stdin);
    //快读一个数
    int num = 0;
    while ((c = getchar()) >= '0' && c <= '9')
        num = num * 10 + c - '0';
    ungetc(c, stdin); //最后一定多读了一个才能判断不在数字内

    return positive ? num : -num;
}

bool is_leaf(int path_sum)
{
    //找到答案也不能立刻返回，要读完所有的数
    char c;
    int num;

    get_blank_and_char();                  //读取左括号
    if ((c = get_blank_and_char()) == ')') //读了所有的空白字符，如果直接是右括号了
        return true;
    else                                       //不是右括号那就是数字了
        ungetc(c, stdin), num = get_integer(); //读取数字

    bool l_is_leaf = is_leaf(path_sum + num);             //看左子树是否只有一对括号
    bool r_is_leaf = is_leaf(path_sum + num);             //看右子树是否只有一对括号
    if (l_is_leaf && r_is_leaf && path_sum + num == goal) //左右均是括号且路径和为目标数字
        has_path = true;

    get_blank_and_char(); //读取右括号
    return false;         //不是只有括号的叶子节点
}

int main()
{
    while (~scanf("%d", &goal)) //当不是-1(EOF)时
    {
        has_path = false;
        is_leaf(0);
        puts(has_path ? "yes" : "no"); // puts会自动补充换行符
    }
}