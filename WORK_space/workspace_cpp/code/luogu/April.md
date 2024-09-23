# 没有上司的舞会

## 题目描述

某大学有 $n$ 个职员，编号为 $1\ldots n$。

他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。

现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数 $r_i$，但是呢，如果某个职员的直接上司来参加舞会了，那么这个职员就无论如何也不肯来参加舞会了。

所以，请你编程计算，邀请哪些职员可以使快乐指数最大，求最大的快乐指数。

## 输入格式

输入的第一行是一个整数 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行一个整数，第 $(i+1)$ 行的整数表示 $i$ 号职员的快乐指数 $r_i$。

第 $(n + 2)$ 到第 $2n$ 行，每行输入一对整数 $l, k$，代表 $k$ 是 $l$ 的直接上司。

## 输出格式

输出一行一个整数代表最大的快乐指数。

## 样例 #1

### 样例输入 #1

```
7
1
1
1
1
1
1
1
1 3
2 3
6 4
7 4
4 5
3 5
```

### 样例输出 #1

```
5
```

## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1\leq n \leq 6 \times 10^3$，$-128 \leq r_i\leq 127$，$1 \leq l, k \leq n$，且给出的关系一定是一棵树。
```c++
#include<iostream>
#include<vector>
#include<cstring>
#define  MAXN  6005

using namespace std;

//P1352  没有上司的舞会
vector<int> son[MAXN];

int  dp[MAXN][2] ,help[MAXN];

void DP(int x)
{
    for(int  i = 0 ; i < son[x].size() ; i++)
    {
        int y = son[x][i];
        DP(y);
        dp[x][0] += max(dp[y][0] , dp[y][1]);
        dp[x][1] += dp[y][0];
    }
}

int main()
{    
    int n ;
    cin >> n ;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> dp [i][1] ;
    }
    for (int i = 1 ; i<= n-1  ; i++)
    {
        int low , upp ;
        cin >> low >> upp;
        son[upp].push_back(low);
        help[low] = 1 ;
    }
    int root ;
    for(int i = 1 ; i <= n ; i++)
    {
        if(!(help[i]))
        {
            root = i ;
            break;
        }
    }
    DP(root) ;
    cout << max(dp[root][0], dp[root][1]);    
}
```

# 最大子树和

## 题目描述

小明对数学饱有兴趣，并且是个勤奋好学的学生，总是在课后留在教室向老师请教一些问题。一天他早晨骑车去上课，路上见到一个老伯正在修剪花花草草，顿时想到了一个有关修剪花卉的问题。于是当日课后，小明就向老师提出了这个问题：

一株奇怪的花卉，上面共连有 $N$ 朵花，共有 $N-1$ 条枝干将花儿连在一起，并且未修剪时每朵花都不是孤立的。每朵花都有一个“美丽指数”，该数越大说明这朵花越漂亮，也有“美丽指数”为负数的，说明这朵花看着都让人恶心。所谓“修剪”，意为：去掉其中的一条枝条，这样一株花就成了两株，扔掉其中一株。经过一系列“修剪“之后，还剩下最后一株花（也可能是一朵）。老师的任务就是：通过一系列“修剪”（也可以什么“修剪”都不进行），使剩下的那株（那朵）花卉上所有花朵的“美丽指数”之和最大。

老师想了一会儿，给出了正解。小明见问题被轻易攻破，相当不爽，于是又拿来问你。

## 输入格式

第一行一个整数 $n\ (1\le N\le 16000)$。表示原始的那株花卉上共 $n$ 朵花。

第二行有 $n$ 个整数，第 $i$ 个整数表示第 $i$ 朵花的美丽指数。

接下来 $n-1$ 行每行两个整数 $a,b$，表示存在一条连接第 $a$ 朵花和第 $b$ 朵花的枝条。

## 输出格式

一个数，表示一系列“修剪”之后所能得到的“美丽指数”之和的最大值。保证绝对值不超过 $2147483647$。

## 样例 #1

### 样例输入 #1

```
7
-1 -1 -1 1 1 1 0
1 4
2 5
3 6
4 7
5 7
6 7
```

### 样例输出 #1

```
3
```

## 提示

### 数据范围及约定

- 对于 $60\%$ 的数据，有 $1\le N\le 1000$；
- 对于 $100\%$ 的数据，有 $1\le N\le 16000$。
```c++
#include<iostream>
#include<vector>
#include<cstring>
#include <climits>
#define MAXN 16001

using namespace std ;
int ans[MAXN];
void DFS(int x, int y ,int (&ans)[MAXN], vector<int> (&other)[MAXN], int (&f)[MAXN])
{
    ans[x] = f[x] ;
    for(int i = 0 ; i < other[x].size() ; i++)
    {
        int temp = other[x][i];
        if(temp != y)
        {
            DFS(temp , x ,ans ,other ,f);
            if(ans[temp] > 0)
            {
                ans[x] += ans[temp] ;
            }
        }
    }
}

int main()
{
    vector<int> other[MAXN];
    int n , f[MAXN];
    memset(f,0,sizeof(f));
    cin >> n;
    for(int i = 1 ; i <= n ; i++ )
    {
        cin >> f[i] ;
    }
    for(int i = 1 ; i <= n-1 ; i++)
    {
        int first , second ;
        cin >> first >> second ;
        other[first].push_back(second) ;
        other[second].push_back(first) ;
    }
    DFS(1,0,ans,other ,f);
    int ansl =INT_MIN; 
    for(int i = 1 ; i <= n ; i++)
    {
        ansl = max(ansl , ans[i]);
    }
    cout<<ansl;
    return 0;
}
```
