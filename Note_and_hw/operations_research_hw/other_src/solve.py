import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

# 距离矩阵
times = np.array([
    [0, 5, 4.5, 6, 8],
    [5, 0, 5.5, 1.25, 14],
    [4.5, 5.5, 0, 5, 9.5],
    [6, 1.25, 5, 0, 12.5],
    [8, 14, 9.5, 12.5, 0]
])

# 创建无向图
G = nx.Graph()

# 添加边和权重
for i in range(len(times)):
    for j in range(i+1, len(times)):
        G.add_edge(i, j, weight=times[i, j])

# 使用Kruskal算法找到最小生成树
mst = nx.minimum_spanning_tree(G, algorithm='kruskal')
mst_weight = mst.size(weight='weight')

# 计算总距离
additional_cost = 4 * (len(times) - 1)
total_distance = mst_weight + additional_cost

# 打印结果
print("最小生成树的权重:", mst_weight)
print("额外的连接代价:", additional_cost)
print("总距离:", total_distance)

# 绘制图像
pos = nx.spring_layout(G)  # 使用弹簧布局以更好地展示图像
plt.figure(figsize=(10, 7))

# 绘制原始图
nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=500, font_size=10, font_weight='bold')
labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_size=8)

# 绘制最小生成树
mst_edges = list(mst.edges(data=True))
nx.draw_networkx_edges(G, pos, edgelist=mst_edges, width=2, edge_color='red')

plt.title("Minimum Spanning Tree with Additional Cost")
plt.show()
