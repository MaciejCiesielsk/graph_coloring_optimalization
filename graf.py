import networkx as nx
import matplotlib.pyplot as plt

def greedy_coloring(graph):
    # Initialize colors for each node
    colors = {}
    for node in graph.nodes():
        # Get all neighbor colors
        neighbor_colors = {colors[neighbor] for neighbor in graph.neighbors(node) if neighbor in colors}
        # Assign the smallest available color
        color = 0
        while color in neighbor_colors:
            color += 1
        colors[node] = color
    return colors

# Define the graph
G = nx.Graph()
edges = [
    ('A', 'B'), ('A', 'C'), ('B', 'D'), ('C', 'E'), 
    ('D', 'F'), ('E', 'F'), ('A', 'D'), ('B', 'E'), ('C', 'F')
]
G.add_edges_from(edges)

# Perform greedy coloring
node_colors = greedy_coloring(G)

# Map color numbers to matplotlib colors
color_map = plt.cm.get_cmap('tab10', max(node_colors.values()) + 1)
node_color_list = [color_map(node_colors[node]) for node in G.nodes()]

# Draw the graph
plt.figure(figsize=(8, 6))
pos = nx.spring_layout(G)  # Positions for nodes
nx.draw(G, pos, with_labels=True, node_color=node_color_list, edge_color='black', node_size=800, font_size=10, font_weight='bold')
plt.title("Greedy Coloring of a Graph", fontsize=14)
plt.show()
