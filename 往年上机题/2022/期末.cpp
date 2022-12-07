//拼写检查
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

unordered_map<string, int> lib;
unordered_set<string> similar; //除重
vector<string> ans;            //按顺序输出的答案
bool cmp(const string a, const string b)
{
    return lib[a] < lib[b];
}
void find_del(string a)
{
    int len = a.length();
    for (int i = 0; i < len; i++)
    {
        string tmp = a;
        tmp.erase(i, 1);
        if (lib[tmp])
            similar.insert(tmp);
    }
}
void find_replace(string a)
{
    int len = a.length();
    string tmp = a;
    for (int i = 0; i < len; i++)
    {
        for (char j = 'a'; j <= 'z'; j++)
        {
            tmp[i] = j;
            if (lib[tmp])
                similar.insert(tmp);
        }
        tmp[i] = a[i];
    }
}
void find_add(string a)
{
    int len = a.length();
    for (int i = 0; i <= len; i++)
    {
        string tmp = a;
        tmp.insert(tmp.begin() + i, 'a');
        for (char j = 'a'; j <= 'z'; j++)
        {
            tmp[i] = j;
            if (lib[tmp])
                similar.insert(tmp);
        }
    }
}
void search(string &a)
{
    if (lib[a])
    {
        cout << a << " is correct\n";
        return;
    }
    similar.clear(), ans.clear();
    find_del(a);
    find_replace(a);
    find_add(a);
    for (auto &i : similar)
        ans.push_back(i);
    sort(ans.begin(), ans.end(), cmp);
    cout << a << ':';
    for (auto &i : ans)
        cout << ' ' << i;
    cout << endl;
}
int main()
{
    int cnt = 0;
    string tmp;
    while (cin >> tmp && tmp != "#")
        lib[tmp] = ++cnt;
    while (cin >> tmp && tmp != "#")
        search(tmp);
}

// card stacking
#include <iostream>
#include <queue>
#include <set>
using namespace std;

int main()
{
    int n, m, p; // n张卡，m个人，洗一次牌切p张
    cin >> m >> n >> p;
    queue<int> q;
    set<int> ans;
    for (int i = 1; i <= n; i++)
        q.push(i);
    for (int i = 1; i <= n / m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j == m)
                ans.insert(q.front());
            q.pop();
            for (int k = 1; k <= p; k++)
                q.push(q.front()), q.pop();
        }
    }
    for (auto i : ans)
        cout << i << endl;
}

//字符串插入
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string str1, str2;
    while (cin >> str1 >> str2)
    {
        int pos = max_element(str1.begin(), str1.end()) - str1.begin(); // max_element函数返回最大元素的迭代器，可以用来求最大元素的下标
        str1.insert(pos + 1, str2);
        cout << str1 << endl;
    }
}

//前缀中的周期
#include <iostream>
#include <string>
using namespace std;

int nxt[1000001] = {0};
int main()
{
    int len, N = 0;
    while (cin >> len && len)
    {
        cout << "Test case #" << ++N << endl;
        string a;
        cin >> a;
        int p = 1, prefix_len = 0; // prefix_len为当前共同前后缀的长度
        //计算next数组
        while (p < len) // next[p]
        {
            if (a[prefix_len] == a[p])
                nxt[p++] = ++prefix_len;
            else
            {
                if (prefix_len == 0)
                    nxt[p++] = 0;
                else
                    prefix_len = nxt[prefix_len - 1];
            }
        }
        for (int i = 2, rep = 2 - nxt[1]; i <= len; i++, rep = i - nxt[i - 1]) //利用next数组的共同前后缀性质得到重复子串
            if (rep != i && (i % rep == 0))
                cout << i << ' ' << i / rep << endl;
        cout << endl;
    }
}

//多项式加法
#include <iostream>
#include <map>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        map<int, int, greater<int>> cnt;
        int a, b;
        while (cin >> a >> b && b >= 0)
            cnt[b] += a;
        while (cin >> a >> b && b >= 0)
            cnt[b] += a;
        for (auto i : cnt)
            if (i.second)
                cout << "[ " << i.second << ' ' << i.first << " ] ";
        cout << endl;
    }
}

//位查询
#include <iostream>
using namespace std;

unsigned int info[100000];
int main()
{
    int m, n, op;
    char c;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        cin >> info[i];
    //数据不harsh，双重循环即可
    while (n--)
    {
        cin >> c >> op;
        if (c == 'C')
            for (int i = 0; i < m; i++)
                info[i] += op;
        else
        {
            int cnt = 0;
            for (int i = 0; i < m; i++)
                cnt += ((info[i] >> op) & 1);
            cout << cnt << endl;
        }
    }
}
// Filp Game
#include <iostream>
using namespace std;
// 0是白，1是黑，全变成一个颜色；1是按，0不按
int ori[6][6] = {{0}}, push[6][6];
int ok()
{
    int cnt1 = 0, cnt2 = 0;
    for (int i = 2; i <= 5; i++) //全按成白的
        for (int j = 1; j <= 4; j++)
        {
            push[i][j] = ori[i - 1][j] ^ push[i - 1][j - 1] ^ push[i - 1][j] ^ push[i - 1][j + 1] ^ push[i - 2][j]; //(i,j)按or不按，能让ori[i-1][j]变成白色
            cnt1 += push[i][j];
        }
    for (int i = 1; i <= 4; i++)
        if (push[5][i])
            cnt1 = 0x3f3f3f3f;
    for (int i = 2; i <= 5; i++) //全按成黑的
        for (int j = 1; j <= 4; j++)
        {
            push[i][j] = ori[i - 1][j] ^ push[i - 1][j - 1] ^ push[i - 1][j] ^ push[i - 1][j + 1] ^ push[i - 2][j] ^ 1; //把(i,j)反过来按能让ori[i-1][j]变成黑的
            cnt2 += push[i][j];
        }
    for (int i = 1; i <= 4; i++)
        if (push[5][i])
            cnt2 = 0x3f3f3f3f;
    return min(cnt1, cnt2);
}
int main()
{
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            char c;
            cin >> c;
            if (c == 'b')
                ori[i][j] = 1;
        }
    for (int i = 0; i < (1 << 4); i++)
    {
        int cnt = 0;
        for (int j = 1; j <= 4; j++)
            push[1][j] = ((i >> (j - 1)) & 1), cnt += push[1][j];
        cnt += ok();
        ans = min(ans, cnt);
    }
    cout << (ans >= 0x3f3f3f3f ? "Impossible" : to_string(ans)) << endl;
}
// Number Sequence
#include <iostream>
using namespace std;

int a[50000] = {0}, b[50000] = {0}; // 序列1...i的位数和数字i的位数
int main()
{
    for (int i = 1; i < 50000; i++)
        b[i] = to_string(i).length(), a[i] = a[i - 1] + b[i];
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        for (int i = 1; i < 50000; i++) //枚举每一个1...i序列
            if (n <= a[i])
                for (int j = 1; j < 50000; j++) //如果在1...i序列中，枚举1...i序列里每一个数字j
                    if (n <= b[j])
                    {
                        cout << to_string(j)[n - 1] << endl;
                        goto loop;
                    }
                    else
                        n -= b[j];
            else
                n -= a[i];
    loop:;
    }
}
//放苹果
#include <iostream>
using namespace std;

int a[11][11] = {{0}};
int f(int m, int n)
{
    if (m == 1 || m == 0 || n == 1)
        return 1;
    else if (a[m][n])
        return a[m][n];
    if (m >= n)
        a[m][n] = f(m - n, n) + f(m, n - 1);
    else
        a[m][n] = f(m, n - 1);
    return a[m][n];
}
int main()
{

    int N;
    cin >> N;
    while (N--)
    {
        int m, n;
        cin >> m >> n;
        cout << f(m, n) << endl;
    }
}
// A Knight's Journey
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

//一定可以从(1, 1)开始，按字典序深搜得到答案
// DFS的参数都可以变成全局变量，要恰当决定哪些变成全局变量
//比如这个题，一些题解的第三个参数是与(1, 1)的距离，我们可以把他与全局变量的防止重复搜索的vis数组合并，简化DFS的参数
int m, n, dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1}, dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2}, dis[28][28] = {{0}}; // dis是vis与距(1, 1)距离的数组合并得到的
vector<string> ans;
bool all_end = false;
void dfs(int x, int y)
{
    if (dis[x][y] == m * n - 1)
    {
        for (auto i : ans)
            cout << i;
        cout << endl
             << endl;
        all_end = true;
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];
        if (xx < 1 || xx > m || yy < 1 || yy > n || (dis[xx][yy] != 0x3f3f3f3f))
            continue;
        dis[xx][yy] = dis[x][y] + 1;
        ans.push_back(char(yy - 1 + 'A') + to_string(xx));
        dfs(xx, yy);
        if (all_end)
            return;
        ans.pop_back();
        dis[xx][yy] = 0x3f3f3f3f;
    }
}
int main()
{
    int N;
    cin >> N;
    for (int T = 1; T <= N; T++)
    {
        printf("Scenario #%d:\n", T);
        memset(dis, 0x3f, sizeof(dis));
        ans.clear();
        all_end = false;
        cin >> m >> n;
        ans.push_back("A1");
        dis[1][1] = 0;
        dfs(1, 1);
        if (!all_end)
            cout << "impossible\n\n";
    }
}
//神奇的幻方
#include <iostream>
using namespace std;

int main()
{
    int n, a[40][40] = {{0}}, x, y;
    cin >> n;
    n = 2 * n - 1, x = 1, y = n / 2 + 1;
    for (int i = 1; i <= n * n; i++)
    {
        a[x][y] = i;
        if (a[x - 1][y + 1] || (x == 1 && y == n))
            x++;
        else if (x == 1)
            x = n, y++;
        else if (y == n)
            x--, y = 1;
        else
            x--, y++;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}
//螺旋方阵的奥秘
#include <iostream>
using namespace std;

int main()
{
    int n, k, a[32][32] = {{0}}, dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0}, x = 1, y = 1, dir = 0;
    cin >> n >> k;
    for (int i = 1; i <= n * n; i++)
    {
        a[x][y] = i;
        if (a[x][y] == k)
        {
            cout << x << ' ' << y;
            return 0;
        }
        int xx = x + dx[dir], yy = y + dy[dir];
        if (xx < 1 || xx > n || yy < 1 || yy > n || a[xx][yy])
            dir = (dir + 1) % 4;
        x = x + dx[dir], y = y + dy[dir];
    }
}

// 0301 滑动窗口
#include <iostream>
#include <deque>
using namespace std;

int info[1000001] = {0};
deque<int> dq;
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> info[i];
    for (int i = 1; i <= n; i++)
    {
        while (!dq.empty() && i - dq.front() >= k)
            dq.pop_front();
        while (!dq.empty() && info[dq.back()] >= info[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k)
            cout << info[dq.front()] << ' ';
    }
    cout << endl;
    dq.clear();
    for (int i = 1; i <= n; i++)
    {
        while (!dq.empty() && i - dq.front() >= k)
            dq.pop_front();
        while (!dq.empty() && info[dq.back()] <= info[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k)
            cout << info[dq.front()] << ' ';
    }
}

// 0302 中缀表达式的值（无空格）
#include <iostream>
#include <stack>
#include <deque>
using namespace std;

stack<char> op;
stack<int> ans;
int priority(char op) //要使括号优先级最高！！！
{
    if (op == '(' || op == ')')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}
void calculate(char op) //对后缀表达式每一个运算符进行计算
{
    int y = ans.top();
    ans.pop();
    int x = ans.top();
    ans.pop();
    switch (op)
    {
    case '+':
        ans.push(x + y);
        break;
    case '-':
        ans.push(x - y);
        break;
    case '*':
        ans.push(x * y);
        break;
    case '/':
        ans.push(x / y);
        break;
    }
}
int main()
{
    int N, len;
    cin >> N;
    while (N--)
    {
        string f;
        cin >> f;
        len = f.length();
        for (int i = 0; i < len; i++)
        {
            if (f[i] < '0' || f[i] > '9') //表达式遇到符号
                //遇到右括号就计算所有括号内的运算符
                if (f[i] == ')')
                {
                    while (op.top() != '(')
                        calculate(op.top()), op.pop();
                    op.pop(); //删除左括号
                }
                // 1.待定符号栈为空 2.这个符号是某个括号内的唯一运算符 3.当前运算符应该更早算（即当前运算符优先级更高，包含括号的优先级！！！）就直接压栈
                else if (op.empty() || op.top() == '(' || priority(f[i]) > priority(op.top()))
                    op.push(f[i]);
                //计算op栈内的一个符号
                else
                    calculate(op.top()), op.pop(), i--; //回溯一次i，从而使下一次循环仍然比较当前的运算符
            else
            {
                string tmp;
                while (f[i] >= '0' && f[i] <= '9')
                    tmp += f[i], i++;
                i--; //回溯一次i，从而使下一次循环仍然比较下一个的运算符
                ans.push(atoi(tmp.c_str()));
            }
        }
        while (!op.empty())
            calculate(op.top()), op.pop();
        cout << ans.top() << endl;
        ans.pop();
    }
}

// 0303 用队列对扑克牌排序
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    string all[100];
    queue<string> num[9], alg[4];
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> all[i];
        num[all[i][1] - '1'].push(all[i]);
    }
    for (int i = 0; i < 9; i++)
    {
        printf("Queue%d:", i + 1);
        while (!num[i].empty())
            cout << num[i].front() << ' ', alg[num[i].front()[0] - 'A'].push(num[i].front()), num[i].pop();
        cout << endl;
    }
    for (int i = 0; i < 4; i++)
    {
        printf("Queue%c:", i + 'A');
        while (!alg[i].empty())
            cout << alg[i].front() << ' ', alg[i].pop();
        cout << endl;
    }
    sort(all, all + N);
    for (int i = 0; i < N; i++)
        cout << all[i] << ' ';
}

// 0304 表达式求值（有乘方，有空格，即可能有负数）
#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

stack<char> op;
stack<int> ans;
int priority(char op)
{
    if (op == '(' || op == ')')
        return 4;
    else if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}
void calculate(char op)
{
    int y = ans.top();
    ans.pop();
    int x = ans.top();
    ans.pop();
    switch (op)
    {
    case '+':
        ans.push(x + y);
        break;
    case '-':
        ans.push(x - y);
        break;
    case '*':
        ans.push(x * y);
        break;
    case '/':
        ans.push(x / y);
        break;
    case '^':
        ans.push(pow(x, y));
        break;
    }
}
int main()
{
    int N, len;
    cin >> N, cin.ignore();
    while (N--)
    {
        string f, tmp;   //有空格分割的使用字符串函数，因为有可能出现负数
        getline(cin, f); // cin和get不消除\n，而getline消除\n！！！
        len = f.length();
        while (!f.empty())
        {
            tmp = f.substr(0, f.find(' '));
            f.erase(0, f.find(' '));
            f.erase(0, 1); //消除空格
            // string::find(int pos, int len)不到就返回string::npos!!!
            //只剩下一个操作数则f.find(' ') 返回unsigned int最大值，如果f.erase(0, f.find(' ') + 1) 则会溢出导致最后一个操作数一直不被删除
            if ((tmp[0] >= '0' && tmp[0] <= '9') || (tmp[0] == '-' && tmp.length() > 1))
                ans.push(atoi(tmp.c_str()));
            else if (tmp[0] == ')')
            {
                while (op.top() != '(')
                    calculate(op.top()), op.pop();
                op.pop();
            }
            else if (op.empty() || op.top() == '(' || priority(tmp[0]) > priority(op.top()))
                op.push(tmp[0]);
            else
                calculate(op.top()), op.pop(), f.insert(0, tmp + ' '); //回溯一次，从而使下一次循环仍然比较当前的运算符
        }
        while (!op.empty())
            calculate(op.top()), op.pop();
        cout << ans.top() << endl;
        ans.pop();
    }
}

// 0306 堆栈基本操作
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
    int n, p = 1;
    cin >> n;
    stack<int> s;
    string ans;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (tmp < 1 || tmp > n || (!s.empty() && tmp < s.top()))
        {
            cout << "NO" << endl;
            return 0;
        }
        else if (!s.empty() && tmp == s.top())
            ans += "POP " + to_string(tmp) + "\n", s.pop();
        else
        {
            for (; p <= tmp; p++)
                ans += "PUSH " + to_string(p) + "\n", s.push(p);
            ans += "POP " + to_string(tmp) + "\n", s.pop();
        }
    }
    cout << ans;
}

// 0309 我是最快的马
#include <iostream>
#include <string>
#include <queue>
using namespace std;

int dx[8] = {-1, -2, -2, -2, 1, 2, 2, 1}, dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int main()
{
    int map[11][11][3] = {{{0}}}; //最短距离，有几种方案，有无其它棋子
    string ans[11][11];           //最短方案是什么
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            map[i][j][0] = 0x3f3f3f3f, map[i][j][1] = 0;
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    map[sx][sy][0] = 0, map[sx][sy][1] = 1, ans[sx][sy] = "(0,0)";
    int N;
    cin >> N;
    while (N--)
    {
        int ox, oy;
        cin >> ox >> oy;
        map[ox][oy][2] = 1;
    }
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while (!q.empty())
    {
        int nx = q.front().first, ny = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int xx = nx + dx[i], yy = ny + dy[i];
            //超出范围，有棋子，别马腿
            if (xx < 0 || xx > 10 || yy < 0 || yy > 10 || map[xx][yy][2] || map[nx + dx[i] / 2][ny + dy[i] / 2][2])
                continue;
            if (map[xx][yy][0] < map[nx][ny][0] + 1)
                continue;
            else if (map[xx][yy][0] == map[nx][ny][0] + 1)
                map[xx][yy][1]++;
            else
                map[xx][yy][0] = map[nx][ny][0] + 1, map[xx][yy][1] = 1, ans[xx][yy] = ans[nx][ny] + "-(" + to_string(xx) + "," + to_string(yy) + ")", q.push({xx, yy});
        }
    }
    cout << (map[ex][ey][1] == 1 ? ans[ex][ey] : to_string(map[ex][ey][1])) << endl;
}

// 0407 去除C程序中的注释
#include <iostream>
using namespace std;

//注释里的字符串是注释
//字符串里的注释是字符串
//注释和字符串互不影响
//转义字符只会影响字符串中右引号的位置
int main()
{
    char p, q;
    while (cin.get(p))
    {
        if (p == '/' && cin.peek() == '*')
        {
            cin.get(); //吃掉 *
            while (cin.get(p))
                if (p == '*' && cin.peek() == '/')
                {
                    cin.get(); //吃掉 / !!!
                    break;
                }
        }
        else if (p == '\'' || p == '"')
        {
            cout << p;                            //输出左引号
            while (cin.get(q) && p != q)          //出现右引号之前一直输出原样的字符
                if (q == '\\')                    //出现转义字符，下一个字符一定是字符串的一部分，直接输出下一个字符
                    cout << q << char(cin.get()); //一定要把cin.get()变成字符，否则输出数字
                else
                    cout << q;
            cout << q; //输出右引号
        }
        else
            cout << p;
    }
}

// 0404 字符串乘方
#include <iostream>
using namespace std;

int nxt[1000010] = {0};
string a;
void Get_Next()
{
    int i = 0, j = -1, l = a.length();
    nxt[0] = -1;
    while (i < l)
        if (j == -1 || a[i] == a[j]) // j == -1!!!
            nxt[++i] = ++j;
        else
            j = nxt[j];
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    while (cin >> a && a != ".")
    {
        Get_Next();
        int len = a.length(), rep = len - nxt[len];
        cout << (len % rep ? 1 : len / rep) << endl;
    }
}

// 0405 Anagram Groups
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define pis pair<int, string>
struct cmp
{
    bool operator()(const pis &a, const pis &b) const
    {
        return (a.first != b.first ? a.first > b.first : a.second < b.second);
    }
};
int main()
{
    map<string, multiset<string>> dict; //字母数量一样的有重等价类
    string cur;
    while (cin >> cur)
    {
        string key = cur;
        sort(key.begin(), key.end());
        dict[key].insert(cur);
    }
    map<pis, set<string>, cmp> sort_groups; //先比较字符串个数再比较第一个字符串大小，同时对字符串集合除重
    for (auto i : dict)
    {
        pis key = {i.second.size(), *i.second.begin()};
        for (auto j : i.second)
            sort_groups[key].insert(j);
    }
    for (int i = 0; i < 5; i++)
    {
        int cnt = (*sort_groups.begin()).first.first;
        set<string> ans = (*sort_groups.begin()).second;
        sort_groups.erase(sort_groups.begin());
        printf("Group of size %d: ", cnt);
        for (auto j : ans)
            cout << j << ' ';
        cout << ".\n";
    }
}

// 0512 文本二叉树
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

// 0510 由中根序列和后根序列重建二叉树
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

// 0514 实现堆结构
#include <iostream>
#include <set>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int N;
    cin >> N;
    while (N--)
    {
        multiset<int> a;
        int n;
        cin >> n;
        while (n--)
        {
            int order;
            cin >> order;
            if (order == 1)
            {
                int k;
                cin >> k;
                a.insert(k);
            }
            else
            {
                cout << *a.begin() << endl;
                a.erase(a.begin());
            }
        }
    }
}

// 0603 发现它，抓住它
#include <iostream>
using namespace std;

// 1~n:帮派A n+1~2n:帮派B f[i]=f[n+j]代表他们不是一个帮派
int f[200010];
int getf(int x)
{
    if (x == f[x])
        return f[x];
    return f[x] = getf(f[x]);
}
void merge(int x, int y)
{
    int fx = getf(x), fy = getf(y);
    f[fx] = fy;
}
int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int m, n;
        cin >> m >> n; //案件 信息
        for (int i = 1; i <= 2 * m; i++)
            f[i] = i;
        for (int i = 1; i <= n; i++)
        {
            char op;
            int x, y;
            cin >> op >> x >> y;
            if (op == 'D')
                merge(x, y + m), merge(x + m, y);
            else
            {
                if (getf(x) == getf(y))
                    cout << "In the same gang.\n";
                else if (getf(x) == getf(y + m) || getf(y) == getf(x + m))
                    cout << "In different gangs.\n";
                else
                    cout << "Not sure yet.\n";
            }
        }
    }
}

// 0606 Shortest Prefixes
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//字典树
struct node
{
    int cnt = 0; //几个单词经过这个节点
    node *ch[26] = {NULL};
};
node *root = new node; // root不算字母
vector<string> word;

void insert(string x)
{
    node *cur = root;
    int len = x.length();
    for (int i = 0; i < len; i++)
    {
        if (!cur->ch[x[i] - 'a'])
            cur->ch[x[i] - 'a'] = new node;
        cur->ch[x[i] - 'a']->cnt++;
        cur = cur->ch[x[i] - 'a'];
    }
}

//找一个字符串最长的无歧义前缀
string find_prefix(string x)
{
    node *cur = root;
    int len = x.length();
    string ans;
    for (int i = 0; i < len; i++)
    {
        if (cur->cnt == 1) // root的时候就加入了第一个字母，因此在遇到cnt==0时，对应的字母已经加入了
            return ans;
        ans += x[i];
        cur = cur->ch[x[i] - 'a'];
    }
    return x;
}

int main()
{
    string tmp;
    while (cin >> tmp)
        word.push_back(tmp), insert(tmp);
    for (auto i : word)
        cout << i << ' ' << find_prefix(i) << endl;
}

// 0608 物质分解记录
#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node
{
    string s;
    Node *father;
    Node *left;
    Node *right;
};

Node *dfs(Node *root, string s)
{
    if (!root)
        return nullptr;
    if (root->s == s)
        return root->right;
    Node *ret;
    ret = dfs(root->left, s);
    if (ret != nullptr)
        return ret;
    ret = dfs(root->right, s);
    return ret;
}

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    while (t--)
    {
        Node *vr = nullptr;
        Node *cur = vr;
        string tmp, last;
        stack<Node *> s;
        bool inited = false;
        while (true)
        {
            last = tmp;
            getline(cin, tmp);
            int len = tmp.length();
            if (len == 0)
                break; // empty line
            if (!inited)
            {
                inited = true;
                vr = new Node{tmp, nullptr, nullptr, nullptr};
                cur = vr;
            }
            if (tmp[0] == '{')
            {
                s.push(cur);
            }
            else if (tmp[0] == '}')
            {
                cur = s.top();
                s.pop();
            }
            else
            {
                if (last == "{")
                {
                    cur->left = new Node{tmp, cur, nullptr, nullptr};
                    cur = cur->left;
                }
                else
                {
                    cur->right = new Node{tmp, cur, nullptr, nullptr};
                    cur = cur->right;
                }
            }
        }
        string toSearch;
        cin >> toSearch;
        Node *ret = dfs(vr, toSearch);
        if (ret)
        {
            while (ret)
            {
                cout << ret->s;
                ret = ret->right;
            }
            cout << '\n';
        }
        else
        {
            cout << "No\n";
        }
        cin.ignore(); // 自分
        getline(cin, tmp);
        getline(cin, tmp);
    }
}

// 0609 表达式·表达式树·表达式求值
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
        { // if is a symbol
            ret += c;
        }
        else if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            while (s.top() != '(')
            { // the string must be valid, so we dont have to check isEmpty
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
    // calc suffixExpr
    string suffix = infix_to_suffix(infix);
    cout << suffix << endl;
    // build exprTree
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

// 0613 树的转换
#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct node
{
    node *l = NULL;
    node *r = NULL;
};
int get_height(node *x)
{
    if (!x)
        return 0;
    else
        return max(get_height(x->l), get_height(x->r)) + 1;
}
int main()
{
    string a;
    int N = 0;
    while (cin >> a && a != "#")
    {
        int h1 = 0, h2 = 0, len = a.length();
        for (int i = 0, h_now = 0; i < len; i++)
            h_now += (a[i] == 'd' ? 1 : -1), h1 = max(h1, h_now);
        node *root = new node;
        node *cur = root;
        stack<node *> pre_root; //在树上的上一层的父节点和同一层的上一个节点
        for (int i = 0; i < len; i++)
            if (a[i] == 'd') //走到树的下一层
            {
                if (!i || a[i - 1] == 'd') //下一层再下一层
                    pre_root.push(cur), cur->l = new node, cur = cur->l;
                else //上一层再下一层
                    cur->r = new node, cur = cur->r;
            }
            else if (!pre_root.empty() && a[i - 1] == 'u')
                cur = pre_root.top(), pre_root.pop();
        h2 = get_height(root);
        printf("Tree %d: %d => %d\n", ++N, h1, h2 - 1);
    }
}

// 0614 宗教信仰
#include <iostream>
#include <set>
using namespace std;

int f[50001];
int find(int x)
{
    return (x == f[x] ? x : f[x] = find(f[x]));
}
void merge(int x, int y)
{
    f[find(y)] = find(x);
}
int main()
{
    int n, m, cnt = 0;
    while (cin >> n >> m && n)
    {
        for (int i = 1; i <= n; i++)
            f[i] = i;
        while (m--)
        {
            int x, y;
            cin >> x >> y;
            merge(x, y);
        }
        set<int> s;
        for (int i = 1; i <= n; i++)
            s.insert(find(i));
        printf("Case %d: ", ++cnt);
        cout << s.size() << endl;
    }
}

// 0615 电话号码
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

// 0616 食物链
#include <iostream>
#include <vector>
using namespace std;

//等价类永远是同一种动物
//将x,x+n,x+2n看成互不相同的元素，x+n代表一个x的虚拟天敌，在1~n的实际存在的个体中不存在
//[n+1,2n]、[2n+1,3n]只起辅助作用，其中元素并不存在
//如果发现x是y的天敌，那么可以确定x和y+n（虚拟天敌）是一种动物，则可以将它们并在一起
#define N 50000
int f[N * 3 + 1];
int find(int x)
{
    return (x == f[x] ? x : f[x] = find(f[x]));
}
void merge(int x, int y)
{
    f[find(y)] = find(x);
}
int main()
{
    for (int i = 1; i <= N * 3; i++)
        f[i] = i;
    int n, k, ans = 0;
    cin >> n >> k;
    while (k--)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (x > n || y > n)
        {
            ans++;
            continue;
        }
        if (op == 1)
        {
            if (find(x) == find(y + n) || find(x) == find(y + 2 * n))
            {
                ans++;
                continue;
            }
            merge(x, y), merge(x + n, y + n), merge(x + 2 * n, y + 2 * n);
        }
        else
        {
            if (x == y || find(x) == find(y) || find(x) == find(y + 2 * n))
            {
                ans++;
                continue;
            }
            merge(x, y + n), merge(x + n, y + 2 * n), merge(x + 2 * n, y);
        }
    }
    cout << ans << endl;
}

// 0617 树上求和
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

// 0702 棋盘问题
#include <iostream>
using namespace std;
int n, k, a[8][8] = {{0}}, ans = 0;
bool col_occupied[8] = {false};
void f(int row, int used)
{
    if (used == k)
    {
        ans++;
        return;
    }
    else if (row == n)
        return;
    for (int i = 0; i < n; i++)
        if (a[row][i] && !col_occupied[i])
            col_occupied[i] = true, f(row + 1, used + 1), col_occupied[i] = false;
    f(row + 1, used);
}
int main()
{
    while (cin >> n >> k && n != -1)
    {
        ans = 0;
        char c;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> c, a[i][j] = c == '#';
        f(0, 0);
        cout << ans << endl;
    }
}

// 0704 Currency Exchange
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define pii pair<int, int>
#define pip pair<int, pair<int, int>>
#define pipdd pair<int, pair<double, double>>

int main()
{
    int n, m, src;
    double ori;
    cin >> n >> m >> src >> ori;
    vector<pipdd> edge[1001];
    for (int i = 0; i < n; i++)
    {
        int f, t;
        double r1, c1, r2, c2;
        cin >> f >> t >> r1 >> c1 >> r2 >> c2;
        edge[f].push_back({t, {r1, c1}}), edge[t].push_back({f, {r2, c2}});
    }
    queue<int> q;
    q.push(src);
    bool in_q[1001] = {false};
    double max_money[1001];
    memset(max_money, 0xc0, sizeof(max_money));
    max_money[src] = ori;
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        in_q[f] = false;
        for (auto &i : edge[f])
        {
            int t = i.first;
            double xr = i.second.first, cms = i.second.second, after = (max_money[f] - cms) * xr;
            if (max_money[t] < after)
            {
                max_money[t] = after;
                if (!in_q[t])
                    q.push(t), in_q[t] = true;
                if (t == src) //源点钱可能增加就说明可以得到更多的钱
                {
                    cout << "YES\n";
                    return 0;
                }
            }
        }
    }
    cout << "NO\n";
    return 0;
}

// 0713 兔子与樱花
#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;
#define pii pair<int, int>
#define pipii pair<int, pair<int, int>>
#define ppiipii pair<pair<int, int>, pair<int, int>>

int main()
{
    unordered_map<int, string> name;
    unordered_map<string, int> id;
    int n;
    cin >> n;
    while (n--)
    {
        string tmp;
        cin >> tmp;
        name[n] = tmp, id[tmp] = n;
    }

    vector<pii> edge[30];
    cin >> n;
    while (n--)
    {
        string n1, n2;
        int w;
        cin >> n1 >> n2 >> w;
        edge[id[n1]].push_back({w, id[n2]});
        edge[id[n2]].push_back({w, id[n1]});
    }

    cin >> n;
    while (n--)
    {
        string s, e;
        cin >> s >> e;
        int sp = id[s], ep = id[e];

        priority_queue<ppiipii, vector<ppiipii>, greater<ppiipii>> q; //距离源的距离，与上一个节点的距离，上一个节点，这一个节点
        for (auto &sp_side : edge[sp])                                //把源点周围的所有点放进队列，相当于已经知道了源点距离源点的距离
            q.push({{sp_side.first, sp_side.first}, {sp, sp_side.second}});

        int dis[30];
        memset(dis, 0x3f, sizeof(dis));
        dis[sp] = 0;

        string path[30];
        path[sp] = s;

        while (!q.empty())
        {
            int w_all = q.top().first.first, w_one = q.top().first.second, pre = q.top().second.first, cur = q.top().second.second;
            q.pop(); //拿出所有信息一定pop

            if (dis[cur] != 0x3f3f3f3f)
                continue;
            else
                dis[cur] = w_all, path[cur] = path[pre] + "->(" + to_string(w_one) + ")->" + name[cur];

            if (dis[ep] != 0x3f3f3f3f) //找到答案
            {
                cout << path[ep] << endl;
                break;
            }
            for (auto &cur_side : edge[cur])
                if (dis[cur_side.second] == 0x3f3f3f3f)
                    q.push({{w_all + cur_side.first, cur_side.first}, {cur, cur_side.second}});
        }
    }
}

//  0714 兔子与星空
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define pip pair<int, pair<int, int>>
int f[128];
int find(int x)
{
    return (x == f[x] ? x : f[x] = find(f[x]));
}
void merge(int x, int y)
{
    f[find(y)] = find(x);
}
int main()
{
    for (int i = 0; i < 128; i++)
        f[i] = i;
    int n;
    cin >> n;
    priority_queue<pip, vector<pip>, greater<pip>> q;
    for (int i = 1; i < n; i++)
    {
        char f;
        int cnt;
        cin >> f >> cnt;
        for (int i = 0; i < cnt; i++)
        {
            char t;
            int w;
            cin >> t >> w;
            q.push({w, {f, t}});
        }
    }
    int ans = 0;
    while (!q.empty())
    {
        int w = q.top().first, x = q.top().second.first, y = q.top().second.second;
        q.pop();
        if (find(x) != find(y))
            ans += w, merge(x, y);
    }
    cout << ans << endl;
}

// 0719 拓扑排序
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n + 1);                     //存边
    vector<int> in(n + 1, 0);                         //入度表
    priority_queue<int, vector<int>, greater<int>> q; //用来每一次找序号最小的入度为0的点（set也可以）
    for (int i = 0; i < m; i++)                       //初始化边与入度表
    {
        int f, t;
        cin >> f >> t;
        e[f].push_back(t);
        in[t]++;
    }
    for (int i = 1; i <= n; i++) //初始化存入度为0的节点的优先队列
        if (!in[i])
            q.push(i);
    while (!q.empty())
    {
        int now = q.top(); //每次删除一个入度为0的节点
        cout << 'v' << now << ' ';
        q.pop();
        for (auto i : e[now]) //出边指向的节点入度--，如果这个节点入度变成0就进队列
        {
            in[i]--;
            if (!in[i])
                q.push(i);
        }
    }
}

// 0802 方便记忆的电话号码
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    int n, replacement[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
    cin >> n;
    map<string, int> a;
    string tmp;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        while (tmp.find('-') != string::npos)       //查找不到不是string::end()
            tmp.erase(tmp.begin() + tmp.find('-')); // string::find()返回下标，string::erase(string::iterator _itr)不是下标
        for (int i = 0; i < tmp.length(); i++)
            if (tmp[i] >= 'A' && tmp[i] <= 'Z')
                tmp[i] = replacement[tmp[i] - 'A'] + '0';
        tmp.insert(tmp.begin() + 3, '-');
        a[tmp]++;
    }
    bool out_put = false;
    for (auto i : a)
        if (i.second - 1)
            out_put = true, cout << i.first << ' ' << i.second << endl;
    if (!out_put)
        cout << "No duplicates." << endl;
}

// 0803 DNA排序
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<string, int> lib;
int f(string &a)
{
    int len = a.length(), ans = 0;
    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
            if (a[i] > a[j])
                ans++;
    return ans;
}

bool cmp(const string &a, const string &b)
{
    return lib[a] < lib[b];
}

int main()
{
    int n, l;
    cin >> l >> n;
    string a[100];
    for (int i = 0; i < n; i++)
        cin >> a[i], lib[a[i]] = f(a[i]);
    stable_sort(a, a + n, cmp);
    for (int i = 0; i < n; i++)
        cout << a[i] << endl;
}

//  0805 Word Amalgamation
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    map<string, set<string>> lib;
    string tmp;
    while (cin >> tmp && tmp != "XXXXXX")
    {
        string key = tmp;
        sort(key.begin(), key.end());
        lib[key].insert(tmp);
    }
    while (cin >> tmp && tmp != "XXXXXX")
    {
        string key = tmp;
        sort(key.begin(), key.end());
        if (lib[key].empty())
            cout << "NOT A VALID WORD\n******\n";
        else
        {
            for (auto &i : lib[key])
                cout << i << endl;
            cout << "******\n";
        }
    }
}

// 0809 求逆序对数
#include <iostream>
using namespace std;
int cnt = 0;
void merge_sort(int l, int r, int *a)
{
    if (l >= r) //不能是等于！！！
        return;
    int mid = (l + r) >> 1;
    merge_sort(l, mid, a), merge_sort(mid + 1, r, a);
    int pl = l, pr = mid + 1, p = l, tmp[20001] = {0};
    while (pl <= mid && pr <= r)
    {
        if (a[pl] <= a[pr])
            tmp[p++] = a[pl++];
        else
            tmp[p++] = a[pr++], cnt += mid - pl + 1; //右边指针指向的小，逆序对为左指针指向的和mid间的部分
    }
    while (pl <= mid)
        tmp[p++] = a[pl++];
    while (pr <= r)
        tmp[p++] = a[pr++];
    for (int i = l; i <= r; i++)
        a[i] = tmp[i];
}
int main()
{
    int n;
    while (cin >> n && n)
    {
        int a[20001] = {0};
        for (int i = 0; i < n; i++)
            cin >> a[i];
        merge_sort(0, n - 1, a);
        cout << cnt << endl;
        cnt = 0;
    }
}

// 0810 距离排序
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct point
{
    int x, y, z;
} pt[10];
struct node_pair
{
    int n1, n2;
    double dis;
    bool operator<(const node_pair &other) const
    {
        return dis > other.dis;
    }
} pr[100];
double f(int a, int b)
{
    return sqrt((pt[a].x - pt[b].x) * (pt[a].x - pt[b].x) + (pt[a].y - pt[b].y) * (pt[a].y - pt[b].y) + (pt[a].z - pt[b].z) * (pt[a].z - pt[b].z));
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> pt[i].x >> pt[i].y >> pt[i].z;
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            pr[cnt++] = node_pair{i, j, f(i, j)}; //可以用大括号直接初始化
    stable_sort(pr, pr + cnt);
    for (int i = 0; i < cnt; i++)
    {
        point a = pt[pr[i].n1], b = pt[pr[i].n2];
        printf("(%d,%d,%d)-(%d,%d,%d)=%.2f\n", a.x, a.y, a.z, b.x, b.y, b.z, pr[i].dis);
    }
}

// 1001 拼写检查
// 重载字符串的比较，按照在字典中的位置比较
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
unordered_map<string, int> dict; //字典，并且用unordered_map储存是字典中的第几个，方便排序（但是map都占内存，不要求按顺序来就用unordered_map）
unordered_set<string> similars;  //找到所有的相似字符串并除重
vector<string> ans;              //对set<string>重载小于号比较麻烦，放进vector再sort

bool cmp(const string a, const string b)
{
    return dict[a] < dict[b];
}

void del_redundant(string tolookup)
{
    int l = tolookup.length();
    for (int i = 0; i < l; i++)
    {
        string tmp = tolookup;
        tmp.erase(i, 1);
        if (dict[tmp])
            similars.insert(tmp);
    }
}

void replace(string tolookup)
{
    int l = tolookup.length();
    string tmp = tolookup;
    for (int i = 0; i < l; i++)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            tmp[i] = c;
            if (dict[tmp])
                similars.insert(tmp);
        }
        tmp[i] = tolookup[i];
    }
}

void add(string tolookup)
{
    int l = tolookup.length();
    for (int i = 0; i <= l; i++)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            string tmp = tolookup;
            tmp.insert(tmp.begin() + i, c);
            if (dict[tmp])
                similars.insert(tmp);
        }
    }
}

void search(const string &tolookup)
{
    cout << tolookup;
    if (dict[tolookup])
        cout << " is correct";
    else
    {
        similars.clear();
        ans.clear();
        del_redundant(tolookup);
        replace(tolookup);
        add(tolookup);
        cout << ":";
        for (auto &item : similars)
            ans.push_back(item);
        sort(ans.begin(), ans.end(), cmp);
        for (auto &item : ans)
            cout << " " << item;
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    string tmp;
    int idx = 0;
    while (cin >> tmp && tmp != "#")
        dict[tmp] = ++idx;
    while (cin >> tmp && tmp != "#")
        search(tmp);
    return 0;
}

// 1002 正方形
#include <iostream>
#include <set>
using namespace std;

int main()
{
    int N;
    while (cin >> N && N)
    {
        set<pair<int, int>> s;
        pair<int, int> tmp;
        while (N--)
            cin >> tmp.first >> tmp.second, s.insert(tmp);
        int ans = 0;
        for (auto &i : s)
            for (auto &j : s)
                if (i < j)
                {
                    int dx = j.first - i.first, dy = j.second - i.second;
                    pair<int, int> ii(i.first + dy, i.second - dx), jj(j.first + dy, j.second - dx);
                    if (s.find(ii) != s.end() && s.find(jj) != s.end())
                        ans++;
                }
        cout << ans / 2 << endl;
    }
}

// 1102 Eqs
#include <iostream>
#include <unordered_map>
using namespace std;

int info[5], cube[101] = {0};
unordered_map<int, int> cnt;
int main()
{
    for (int i = 0; i < 5; i++)
        cin >> info[i];
    for (int i = -50; i <= 50; i++)
        cube[i + 50] = i * i * i;
    for (int i = -50; i <= 50; i++)
        if (i)
            for (int j = -50; j <= 50; j++)
                if (j)
                    cnt[-info[3] * cube[i + 50] - info[4] * cube[j + 50]]++;
    int ans = 0;
    for (int i = -50; i <= 50; i++)
        if (i)
            for (int j = -50; j <= 50; j++)
                if (j)
                    for (int k = -50; k <= 50; k++)
                        if (k)
                            ans += cnt[info[0] * cube[i + 50] + info[1] * cube[j + 50] + info[2] * cube[k + 50]];
    cout << ans << endl;
}

// 1106 倒排文档
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main()
{
    int N, n;
    cin >> N;
    unordered_set<string> s[1001];
    for (int i = 1; i <= N; i++)
    {
        cin >> n;
        string tmp;
        while (n--)
            cin >> tmp, s[i].insert(tmp);
    }
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string tmp;
        cin >> tmp;
        bool ok = false;
        for (int j = 1; j <= N; j++)
            if (s[j].find(tmp) != s[j].end())
                cout << j << ' ', ok = true;
        cout << (ok ? "\n" : "NOT FOUND\n");
    }
}

// 02 开关问题
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n, eq[32] = {0}, tmp, x, y;
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> tmp, eq[i] |= tmp << n, eq[i] |= 1 << i; //自己按自己也要变
        for (int i = 0; i < n; i++)
            cin >> tmp, eq[i] ^= tmp << n;
        while (cin >> x >> y && x && y)
            eq[y - 1] |= 1 << (x - 1);
        //对eq进行高斯消元
        int row = 0;                                        //最新的方程是哪一行
        for (int col = 0; col < n && row < n; col++, row++) //每次处理一列
        {
            int i = row;
            while (i < n && !(eq[i] & (1 << col)))
                i++;
            if (i == n) // c处变量全是0，这行方程多一格0
            {
                row--;
                continue;
            }
            if (i > row) //交换两个方程
                swap(eq[row], eq[i]);
            for (int j = row + 1; j < n; j++)
                if (eq[j] & (1 << col))
                    eq[j] ^= eq[row];
        }
        //高斯消元之后eq[row]应该是第一个全0方程
        for (int i = row; i < n; i++)
            if (eq[i] & (1 << n)) //化简的增广阵中存在(0, 0, ..., a)这样的行，无解！
            {
                cout << "Oh,it's impossible~!!\n"; // Oh之后没有空格
                goto loop;
            }
        cout << (1 << (n - row)) << endl;
    loop:;
    }
}

// 06 电话号码
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        vector<string> lib;
        set<string> pre;
        for (int i = 0; i < n; i++)
        {
            string a;
            cin >> a;
            lib.push_back(a);
            int len = a.length();
            for (int j = 1; j < len; j++)
                pre.insert(a.substr(0, j));
        }
        for (auto i : lib)
            if (pre.find(i) != pre.end())
            {
                cout << "NO\n";
                goto loop;
            }
        cout << "YES\n";
    loop:;
    }
}

// 07 Shortest Prefixes
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main()
{
    vector<string> lib;
    map<string, int> pre_cnt; //所有前缀出现的次数
    string a;
    while (cin >> a)
    {
        lib.push_back(a);
        int len = a.length();
        for (int i = 1; i <= len; i++)
            pre_cnt[a.substr(0, i)]++;
    }
    for (auto i : lib)
    {
        int len = i.length();
        for (int j = 1; j <= len; j++)
        {
            string prefix = i.substr(0, j);
            if (pre_cnt[prefix] == 1)
            {
                cout << i << ' ' << prefix << endl;
                goto loop;
            }
        }
        cout << i << ' ' << i << endl;
    loop:;
    }
}

// 11 Snowflake
#include <iostream>
#include <vector>
using namespace std;
//先用hash_table判断是否有有可能，再在所有可能中找是否真的有一样的
#define prime 999983
int info[100000][6];
vector<int> hash_table[prime];

bool is_similar(int x, int y)
{
    for (int delta = 0; delta < 6; delta++) //顺时针比较
    {
        for (int i = 0; i < 6; i++)
            if (info[x][i] != info[y][(i + delta) % 6])
                goto nxt_delta1;
        return true;
    nxt_delta1:;
    }
    for (int delta = 0; delta < 6; delta++) //逆时针比较
    {
        for (int i = 0; i < 6; i++)
            if (info[x][i] != info[y][(6 - i + delta) % 6])
                goto nxt_delta2;
        return true;
    nxt_delta2:;
    }
    return false;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < 6; j++)
            cin >> info[i][j], sum += info[i][j];
        for (auto j : hash_table[sum % prime])
            if (is_similar(i, j))
            {
                cout << "Twin snowflakes found.\n";
                return 0;
            }
        hash_table[sum % prime].push_back(i);
    }
    cout << "No two snowflakes are alike.\n";
}

// 1 词典
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    unordered_map<string, string> dict;
    string a, b;
    while (cin >> a >> b)
    {
        dict[b] = a;
        cin.ignore();
        if (cin.peek() == '\n')
            break;
    }
    while (cin >> a)
    {
        if (dict.find(a) != dict.end())
            cout << dict[a] << endl;
        else
            cout << "eh\n";
    }
}

// 1 Huffman编码树
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            q.push(tmp);
        }
        int sum = 0;
        while (q.size() != 1)
        {
            int tmp = 0;
            tmp += q.top(), q.pop();
            tmp += q.top(), q.pop();
            sum += tmp;
            q.push(tmp);
        }
        cout << sum << endl;
    }
}

// 3 舰队、海域出击！
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//使用邻接矩阵、入度表实现BFS拓扑排序，来判环
vector<int> edge[100001];
vector<int> id_table;
int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            edge[i].clear();
        id_table.clear();
        id_table.resize(n + 1, 0);
        while (m--)
        {
            int x, y;
            cin >> x >> y;
            edge[x].push_back(y);
            id_table[y]++;
        }
        queue<int> q; //入度为0的节点
        int cnt = 0;  //能拓扑排序出来的点的个数
        for (int i = 1; i <= n; i++)
            if (id_table[i] == 0)
                q.push(i);
        while (!q.empty())
        {
            int from = q.front();
            q.pop(), cnt++;
            for (auto to : edge[from])
                if (--id_table[to] == 0)
                    q.push(to);
        }
        cout << (cnt != n ? "Yes\n" : "No\n");
    }
}

// 4 现代艺术
#include <iostream>
#include <stack>
using namespace std;

//一层一层往上堆，如果某一层颜色内部出现了位于其下的颜色则说明最高这层至少涂了两次
int col[100010], s[100010] = {0}, e[100010];
stack<int> st; //栈顶是最后一次染的颜色
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> col[i];
        if (!s[col[i]])
            s[col[i]] = i;
        e[col[i]] = i;
    }
    col[n + 1] = 0, s[0] = 0, e[0] = n + 1;
    st.push(0); //假设最开始全部涂为无色
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == s[col[i]]) // i处的颜色是某个新颜色区间的起始位置
            st.push(col[i]), ans = max(ans, (int)st.size());
        if (col[i] != st.top()) //当前的颜色内部出现了位于其下的颜色
        {
            cout << -1 << endl;
            return 0;
        }
        if (i == e[col[i]])
            st.pop();
    }
    cout << ans - 1 << endl;
}

// 5 越野滑雪
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

//二分BFS
#define pii pair<int, int>
int n, m, info[502][502] = {{0}}, dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
bool check_point[502][502] = {{0}};
pii start;
bool connect(int d)
{
    queue<pii> q;
    q.push(start);
    bool vis[502][502] = {{false}};
    vis[start.first][start.second] = true;
    while (!q.empty())
    {
        pii cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int xx = cur.first + dx[i], yy = cur.second + dy[i];
            if (vis[xx][yy] || abs(info[xx][yy] - info[cur.first][cur.second]) > d)
                continue;
            vis[xx][yy] = true; //放入队列时更新距离（vis）
            q.push({xx, yy});
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (check_point[i][j] && !vis[i][j])
                return false;
    return true;
}

int main()
{
    int l = -1, r = 0xc0c0c0c0, mid;
    memset(info, 0xc0, sizeof(info)); //周围一圈不可能走到
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> info[i][j];
            r = max(r, info[i][j] + 1);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> check_point[i][j];
            start = make_pair(i, j);
        }
    while (l + 1 != r)
    {
        mid = l + (r - l) / 2;
        if (connect(mid))
            r = mid;
        else
            l = mid;
    }
    cout << r << endl;
}

// 1 数字去重
#include <iostream>
#include <unordered_set>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        unordered_set<int> s;
        while (n--)
        {
            int tmp;
            cin >> tmp;
            if (s.find(tmp) != s.end())
                continue;
            cout << tmp << ' ';
            s.insert(tmp);
        }
        cout << endl;
    }
}

// 3 序列的中位数
#include <iostream>
#include <queue>
using namespace std;

long long n, info[100001];
int main()
{
    cin >> n;
    for (long long i = 1; i <= n; i++)
        cin >> info[i];
    priority_queue<long long> l;
    priority_queue<long long, vector<long long>, greater<long long>> r;
    long long mid = info[1];
    cout << mid << endl;
    for (long long i = 2; i <= (n + 1) / 2; i++) //找每一个中位数
    {
        long long a = info[i * 2 - 2], b = info[i * 2 - 1];
        if ((mid - a) * (mid - b) <= 0)
            l.push(min(a, b)), r.push(max(a, b));
        else if (mid < a)
            l.push(mid), r.push(a), r.push(b), mid = r.top(), r.pop();
        else
            l.push(a), l.push(b), r.push(mid), mid = l.top(), l.pop();
        cout << mid << endl;
    }
}

// 5 电话线路
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

//二分SPFA或Dijkstra
#define SPFA
// #define Dijkstra

#define pii pair<int, int>
int n, m, k;
bool no_path = false; //注意判断无路径-1
vector<pii> edge[1001];
// 找1->n的最短路径，大于x算长度为1，最短路径<=k时该价钱可以建起来线路
bool possible_price(int x)
{

#ifdef SPFA

    // SPFA
    queue<int> q;
    q.push(1);
    bool in_queue[1001] = {false};
    in_queue[1] = true;
    int dis[1001];
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    while (!q.empty())
    {
        int cur = q.front(); //下一个用来作为松弛起点的点
        q.pop();             //与Dijkstra和Prim等贪心算法不同，SPFA是一直松弛，不用判定是否非法（指已有最短路径）
        in_queue[cur] = false;
        for (auto e : edge[cur])
            if (dis[e.second] > dis[cur] + (e.first > x)) //可以被松弛
            {
                dis[e.second] = dis[cur] + (e.first > x);
                if (!in_queue[e.second]) //如果队列中没有松弛终点，那么把松弛终点放入队列
                    q.push(e.second), in_queue[e.second] = true;
            }
    }
    if (dis[n] == 0x3f3f3f3f)
        no_path = true;
    return dis[n] <= k;

#endif

#ifdef Dijkstra

    // Dijkstra
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, 1});
    int dis[1001]; //最开始没有有最短路径的点，不要初始化dis[0] = 0
    memset(dis, 0x3f, sizeof(dis));
    while (!q.empty())
    {
        int cur = q.top().second;   //下一个扩入的节点，这个节点的距离只是用来贪心排序的，不用放进cur
        if (dis[cur] != 0x3f3f3f3f) //贪心算法一定先判断是否已经有了最短路径，因为可能许多一样的节点有不同的距离都在队列里
        {
            q.pop(); //没用的节点一定要pop
            continue;
        }
        dis[cur] = q.top().first; //找到最短路径之后再更新dis
        q.pop();
        for (auto e : edge[cur])             //查看一圈节点
            if (dis[e.second] == 0x3f3f3f3f) //把所有未产生最短路径的节点与其可能的最短路径放入队列
                q.push({dis[cur] + (e.first > x), e.second});
    }
    if (dis[n] == 0x3f3f3f3f)
        no_path = true;
    return dis[n] <= k;

#endif
}

int main()
{
    cin >> n >> m >> k;
    int l = -1, r = -1, mid = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        edge[a].push_back({w, b});
        edge[b].push_back({w, a});
        r = max(r, w + 1);
    }
    while (l + 1 != r)
    {
        mid = l + (r - l) / 2;
        if (possible_price(mid))
            r = mid;
        else
            l = mid;
    }
    cout << (no_path ? -1 : r) << endl;
}

// 1 括号替换
#include <iostream>
#include <stack>
using namespace std;
//如果 s1，s2 是RBS，则 s2， {s1}s2，[s1]s2，(s1)s2 也是RBS，<s1>s2也是！！！
//每遇到一个右括号都要使得它与一个左括号匹配，用栈维护未匹配的左括号
int main()
{
    stack<char> s;
    int cnt = 0, x;
    char brkt[128];
    brkt['<'] = brkt['{'] = brkt['['] = brkt['('] = 'l';
    brkt['>'] = brkt['}'] = brkt[']'] = brkt[')'] = 'r';
    char pair[128];
    pair['>'] = '<', pair['}'] = '{', pair[']'] = '[', pair[')'] = '(';
    while ((x = getchar()) != '\n')
    {
        if (brkt[x] == 'l')
            s.push(x);
        else
        {
            if (s.empty())
            {
                cout << "Impossible\n";
                return 0;
            }
            cnt += pair[x] != s.top(), s.pop();
        }
    }
    if (!s.empty())
    {
        cout << "Impossible\n";
        return 0;
    }
    cout << cnt << endl;
}

// 2 拼写检查
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

unordered_map<string, int> lib;
unordered_set<string> similar; //除重
vector<string> ans;            //按顺序输出的答案
bool cmp(const string a, const string b)
{
    return lib[a] < lib[b];
}
void find_del(string a)
{
    int len = a.length();
    for (int i = 0; i < len; i++)
    {
        string tmp = a;
        tmp.erase(i, 1);
        if (lib[tmp])
            similar.insert(tmp);
    }
}
void find_replace(string a)
{
    int len = a.length();
    string tmp = a;
    for (int i = 0; i < len; i++)
    {
        for (char j = 'a'; j <= 'z'; j++)
        {
            tmp[i] = j;
            if (lib[tmp])
                similar.insert(tmp);
        }
        tmp[i] = a[i];
    }
}
void find_add(string a)
{
    int len = a.length();
    for (int i = 0; i <= len; i++)
    {
        string tmp = a;
        tmp.insert(tmp.begin() + i, 'a');
        for (char j = 'a'; j <= 'z'; j++)
        {
            tmp[i] = j;
            if (lib[tmp])
                similar.insert(tmp);
        }
    }
}
void search(string &a)
{
    if (lib[a])
    {
        cout << a << " is correct\n";
        return;
    }
    similar.clear(), ans.clear();
    find_del(a);
    find_replace(a);
    find_add(a);
    for (auto &i : similar)
        ans.push_back(i);
    sort(ans.begin(), ans.end(), cmp);
    cout << a << ':';
    for (auto &i : ans)
        cout << ' ' << i;
    cout << endl;
}
int main()
{
    int cnt = 0;
    string tmp;
    while (cin >> tmp && tmp != "#")
        lib[tmp] = ++cnt;
    while (cin >> tmp && tmp != "#")
        search(tmp);
}

//