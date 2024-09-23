import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

times = np.array([
    [0, 5, 4.5, 6, 8],
    [5, 0, 5.5, 1.25, 14],
    [4.5, 5.5, 0, 5, 9.5],
    [6, 1.25, 5, 0, 12.5],
    [8, 14, 9.5, 12.5, 0]
])

edges = [(i, j) for i in range(len(times)) for j in range(i + 1, len(times))]
edge_weights = {(i, j): times[i, j] for i, j in edges}
initial_weight = sum(edge_weights.values())
additional_cost = 4 * len(edges)
total_weight = initial_weight + additional_cost
G = nx.Graph()
G.add_edges_from(edges)
best_weight = total_weight
best_combo = edges

for edge in edges:
    G_temp = G.copy()
    G_temp.remove_edge(*edge)
    
    if nx.is_connected(G_temp):
        current_weight = sum(edge_weights[(u, v)] for u, v in G_temp.edges)
        current_additional_cost = 4 * len(G_temp.edges)
        current_total_weight = current_weight + current_additional_cost
        
        if current_total_weight < best_weight:
            best_weight = current_total_weight
            best_combo = list(G_temp.edges)

print("最小总距离:", best_weight)
print("最优连接组合:", best_combo)


G_final = nx.Graph()
G_final.add_edges_from(best_combo)
pos = nx.spring_layout(G_final)  
plt.figure(figsize=(10, 7))
nx.draw(G_final, pos, with_labels=True, node_color='lightblue', node_size=500, font_size=10, font_weight='bold')
labels = nx.get_edge_attributes(G_final, 'weight')
nx.draw_networkx_edge_labels(G_final, pos, edge_labels={edge: edge_weights[edge] for edge in best_combo}, font_size=8)

plt.title("Optimal Connection with Additional Cost")
plt.show()
