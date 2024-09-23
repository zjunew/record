## 3.3
There is an undirected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given an integer array restricted which represents restricted nodes.

Return the maximum number of nodes you can reach from node 0 without visiting a restricted node.

Note that node 0 will not be a restricted node.

>用哈希集合（或者布尔数组）记录哪些节点是受限的。  
然后建树，只有当两个节点都不是受限的（都不在哈希集合中）才连边。  
从 000 出发 DFS 这棵树，统计能访问到的节点个数，即为答案。

```c++
class Solution {
public:
    int DFS(vector<vector<int>>& g , int pos ,int father)
    {
        int cur = 1 ;
        for(auto & y:g[pos])
        {
            if(y != father)
                cur += DFS(g, y , pos);
        }
        return cur;
    }
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        unordered_set<int > r(restricted.begin(),restricted.end());
        vector<vector<int>> g;
        g.resize(n);
        for(auto& e:edges)
        {
            int x = e[0] , y = e[1] ;
            if(!(r.contains(x)||r.contains(y)))
            {
                g[x].push_back(y);
                g[y].push_back(x);
            }   
        }  
        return DFS(g,0,-1);
    }
};
```

You are given a 0-indexed integer array nums. You have to partition the array into one or more contiguous subarrays.

We call a partition of the array valid if each of the obtained subarrays satisfies one of the following conditions:

The subarray consists of exactly 2, equal elements. For example, the subarray [2,2] is good.  
The subarray consists of exactly 3, equal elements. For example, the subarray [4,4,4] is good.  
The subarray consists of exactly 3 consecutive increasing elements, that is, the difference between adjacent   elements is 1. For example, the subarray [3,4,5] is good, but the subarray [1,3,5] is not.  
Return true if the array has at least one valid partition. Otherwise, return false.  


```c++
class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp( n+1 , false);
        dp[0] = true ;
        for( int i = 1 ;i <= n ; i++)
        {
            if(i>=2)
            {
                dp[i] = dp[i-2]&&two(nums[i-2],nums[i-1]);
            }
            if(i>=3)
            {
                dp[i] = dp[i] ||dp[i-3] && three(nums[i-3],nums[i-2],nums[i-1]);
            }
        }
        return dp[n];
    }
    bool two(int a , int b)
    {
        return a==b;
    }
    bool three(int a ,int b,int c)
    {
        if(a==b && a==c)
        {
            return true;
        }
        if( (a+1) == b && (b+1) == c)
        {
            return true;
        }
        return false ;
    }
};
```

You are given an integer n representing the number of nodes in a perfect binary tree consisting of nodes numbered from 1 to n. The root of the tree is node 1 and each node i in the tree has two children where the left child is the node 2 * i and the right child is 2 * i + 1.

Each node in the tree also has a cost represented by a given 0-indexed integer array cost of size n where cost[i] is the cost of node i + 1. You are allowed to increment the cost of any node by 1 any number of times.

Return the minimum number of increments you need to make the cost of paths from the root to each leaf node equal.

Note:

A perfect binary tree is a tree where each node, except the leaf nodes, has exactly 2 children.
The cost of a path is the sum of costs of nodes in the path.

# 3.14
* （952. Largest Component Size by Common Factor）  

You are given an integer array of unique positive integers nums. Consider the following graph:

There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
Return the size of the largest connected component in the graph.

思路：为了得到数组 nums\textit{nums}nums 中的每个数和哪些数属于同一个组件，需要得到数组 nums\textit{nums}nums 中的最大值 mmm，对于每个不超过 mmm 的正整数 num\textit{num}num 计算 num\textit{num}num 和哪些数属于同一个组件。对于范围 [2,num][2, \sqrt{\textit{num}}][2, 
num
​
 ] 内的每个正整数 iii，如果 iii 是 num\textit{num}num 的因数，则 num\textit{num}num 和 iii、numi\dfrac{\textit{num}}{i} 
i
num
​
  都属于同一个组件。

可以使用并查集实现组件的计算。初始时，每个数分别属于不同的组件。如果两个正整数满足其中一个正整数是另一个正整数的因数，则这两个正整数属于同一个组件，将这两个正整数的组件合并。

当所有不超过 mmm 的正整数都完成合并操作之后。遍历数组 nums\textit{nums}nums，对于每个数得到其所在的组件并更新该组件的大小，遍历结束之后即可得到最大组件的大小。

# 3.17
* 310. Minimum Height Trees
A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

>solution:实际做法如下：

首先找到所有度为 111 的节点压入队列，此时令节点剩余计数 remainNodes=n\textit{remainNodes} = nremainNodes=n；

同时将当前 remainNodes\textit{remainNodes}remainNodes 计数减去出度为 111 的节点数目，将最外层的度为 111 的叶子节点取出，并将与之相邻的节点的度减少，重复上述步骤将当前节点中度为 111 的节点压入队列中；

重复上述步骤，直到剩余的节点数组 remainNodes≤2\textit{remainNodes} \le 2remainNodes≤2 时，此时剩余的节点即为当前高度最小树的根节点。

```c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if( n == 1 )
            return {0};
        vector< int > degree (n);
        vector<vector< int >> help(n);
        for( auto & cur : edges)
        {
            help[cur[0]].push_back(cur[1]) ;
            help[cur[1]].push_back(cur[0]) ;
            degree[cur[0]]++;
            degree[cur[1]]++;
        }
        queue<int> qu;
        vector<int > ans ;
        for (int i = 0 ; i < n ; i++ )
        {
            if(degree[i] == 1)
                qu.push( i ) ;
        }
        int remain = n;
        while(remain > 2)
        {
            int size = qu.size();
            remain -= size ;
            for(int i = 0 ;i < size ; i++)
            {
                int cur = qu.front();
                qu.pop();
                for( auto & x : help[cur])
                {
                    if(--degree[x] == 1)
                    {
                        qu.push(x);
                    }
                }
            }
            
        }
        while(!qu.empty())
        {
            ans.push_back(qu.front());
            qu.pop();
        }
        return ans;
    }
};
```
* 2684. Maximum Number of Moves in a Grid
You are given a 0-indexed m x n matrix grid consisting of positive integers.

You can start at any cell in the first column of the matrix, and traverse the grid in the following way:

From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell.

Return the maximum number of moves that you can perform.
```c++
class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        unordered_set<int> q, q2;
        for (int i = 0; i < m; i++) {
            q.insert(i);
        }
        for (int j = 1; j < n; j++) {
            q2.clear();
            for (int i : q) {
                for (int i2 = i - 1; i2 <= i + 1; i2++) {
                    if (0 <= i2 && i2 < m && grid[i][j - 1] < grid[i2][j]) {
                        q2.insert(i2);
                    }
                }
            }
            swap(q, q2);
            if (q.empty()) {
                return j - 1;
            }
        }
        return n - 1;
    }
};
```
```c++
class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        //dp 或者记分板的dfs
        // dp思路：自右上角开始，一列一列遍历，时间复杂度：O(nm)
        // 结果：答案应该在第一列中，可以取第一列的最大值
        // 状态转移方程：
        // dp[i][j] = max(dp[i-1][j+1], dp[i][j+1], dp[i+1][j+1]) 
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // 初始化：最后一列全为0，因为不存在
        // 从倒数第二列开始
        for(int j = n - 2; j >=0; j--){
            for(int i = 0; i < m; i++){
                int mx = 0;
                if(grid[i][j] < grid[i][j+1]){
                    mx = max(mx, dp[i][j+1] + 1);
                }
                if(i + 1 < m && grid[i][j] < grid[i+1][j+1]){
                    mx = max(mx, dp[i+1][j+1] + 1);
                }
                if(i - 1 >= 0 && grid[i][j] < grid[i-1][j+1]){
                    mx = max(mx, dp[i-1][j+1] + 1);
                }
                dp[i][j] = mx;
            }
        }        

        int res = 0;
        for(int i = 0; i < m; i++){
            res = max(res, dp[i][0]);
        }
        return res;
      

    }
};
```

* 337. House Robber III
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.

Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

思路与算法

简化一下这个问题：一棵二叉树，树上的每个点都有对应的权值，每个点有两种状态（选中和不选中），问在不能同时选中有父子关系的点的情况下，能选中的点的最大权值和是多少。

我们可以用 f(o)f(o)f(o) 表示选择 ooo 节点的情况下，ooo 节点的子树上被选择的节点的最大权值和；g(o)g(o)g(o) 表示不选择 ooo 节点的情况下，ooo 节点的子树上被选择的节点的最大权值和；lll 和 rrr 代表 ooo 的左右孩子。

当 ooo 被选中时，ooo 的左右孩子都不能被选中，故 ooo 被选中情况下子树上被选中点的最大权值和为 lll 和 rrr 不被选中的最大权值和相加，即 f(o)=g(l)+g(r)f(o) = g(l) + g(r)f(o)=g(l)+g(r)。
当 ooo 不被选中时，ooo 的左右孩子可以被选中，也可以不被选中。对于 ooo 的某个具体的孩子 xxx，它对 ooo 的贡献是 xxx 被选中和不被选中情况下权值和的较大值。故 g(o)=max⁡{f(l),g(l)}+max⁡{f(r),g(r)}g(o) = \max \{ f(l) , g(l)\}+\max\{ f(r) , g(r) \}g(o)=max{f(l),g(l)}+max{f(r),g(r)}。
至此，我们可以用哈希表来存 fff 和 ggg 的函数值，用深度优先搜索的办法后序遍历这棵二叉树，我们就可以得到每一个节点的 fff 和 ggg。根节点的 fff 和 ggg 的最大值就是我们要找的答案。

我们不难给出这样的实现：

```c++
class Solution {
public:
    unordered_map <TreeNode*, int> f, g;

    void dfs(TreeNode* node) {
        if (!node) {
            return;
        }
        dfs(node->left);
        dfs(node->right);
        f[node] = node->val + g[node->left] + g[node->right];
        g[node] = max(f[node->left], g[node->left]) + max(f[node->right], g[node->right]);
    }

    int rob(TreeNode* root) {
        dfs(root);
        return max(f[root], g[root]);
    }
};
```
```c++
class Solution {
public:
    pair<int, int> dfs(TreeNode *root) {
        if (root == nullptr) {
            return { 0, 0 };
        }
        auto left_pair = dfs(root->left);
        auto right_pair = dfs(root->right);
        return { root->val + left_pair.second + right_pair.second, 
                max(left_pair.first, left_pair.second) + max(right_pair.first, right_pair.second) };
    }
    
    int rob(TreeNode* root) {
        auto p = dfs(root);
        return max(p.first, p.second);
    }
};
```