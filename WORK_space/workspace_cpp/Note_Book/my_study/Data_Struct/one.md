## c中哈希：  
>哈希表在头文件"uthash.h"中已经有了  
```c
#include "uthash.h"
typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} Hash;
Hash *hash = NULL;
```


1.  其中UT_hash_handle是头文件"uthash.h"中定义的，然后Hash结构体是自定义的。
key的类型可以是int, char *, char[]，void* 这4种，value可以是任意类型  

2. HASH_ADD_INT、HASH_FIND_INT、HASH_DEL都是标准函数，其他都是自定义代码。  
```c
// 增加
void add(int key, int value)
{
    Hash *s = NULL;
    s = (Hash *)malloc(sizeof(Hash));
    s->key = key;
    s->value = value;
    HASH_ADD_INT(hash, key, s);
 
}
// 查找
int find(int key)
{
    Hash *s = NULL;
    HASH_FIND_INT(hash, &key, s);
    
    if (s != NULL) {
        // 查找到结果
        return 1;
    } else {
        return 0;
    }
}
// 删除
void delete (Hash *s)
{
    HASH_DEL(hash, s);
    free(s);
    s = NULL;
}
```

```c++
#include <iostream>
#define Max 503
#define INF 0xcffffff

using namespace std;

typedef struct AMGraph {							//定义图
	int vex, arc;
	int arcs[Max][Max];								//邻接矩阵
};

int dis[Max], path[Max];							//dis保存最短路径总权值、path通过保存路径的前驱结点来保存路径
bool book[Max];										//已找到最短路集合

void Dijkstra(AMGraph &G)							//迪杰斯特拉算法
{
	for (int i = 1; i <= G.vex; i++)				
	{
		dis[i] = G.arcs[1][i];						//初始化dis数组
		path[i] = dis[i] < INF ? 1 : -1;			//初始化路径数组
	}
	book[1] = true;									
	dis[1] = 0;										//起点初始化
	for (int i = 2; i <= G.vex; i++)				//遍历G.vex-1次
	{
		int mins = INF, u = 1;
		for (int j = 1; j <= G.vex; j++)			//找到当前没加入集合的最短路的后驱点
		{
			if (!book[j] && mins > dis[j]) {
				mins = dis[j];
				u = j;
			}
		}
		book[u] = true;								//将该点加入集合
		for (int j = 1; j <= G.vex; j++)			//遍历所有其他点对其最短路进行更新（松弛操作）
		{
			if (!book[j] && dis[j] > dis[u] + G.arcs[u][j]) {
				dis[j] = dis[u] + G.arcs[u][j];		//更新最短路径值
				path[j] = u;						//修改j的前驱为u
			}
		}
	}
}

void find(int x)									//递归输出最短路径
{
	if (path[x] == 1) {
		cout << 1;
	}
	else {
		find(path[x]);
	}
	cout << " -> " << x;
	return;
}

void putin(AMGraph &G)								//输入图
{
	cin >> G.vex >> G.arc;
	for (int i = 1; i <= G.vex; i++)				//初始化邻接矩阵
		for (int j = 1; j <= G.vex; j++)
			G.arcs[i][j] = INF;

	for (int i = 1; i <= G.arc; i++)			
	{
		int u, v, w;
		cin >> u >> v >> w;
		G.arcs[u][v] = w;
	}
}

void putout(AMGraph &G)								//输出
{
	//cout << "起点 v1 到各点的最短路程为: \n";
	for (int i = 1; i < G.vex; i++)
	{
		cout << dis[i] << " ";
	}
	cout << dis[G.vex] << endl;
	/*for (int i = 2; i <= G.vex; i++)
	{
		cout << "起点 v1 到 v" << i << " 的路径为： ";
		find(i);
		cout << endl;
	}*/
}

int main()
{
	AMGraph G;
	putin(G);
	Dijkstra(G);
	putout(G);
	return 0;
}

```