import networkx as nx
import matplotlib.pyplot as plt

# Funkcja implementująca zachłanne kolorowanie grafu
def greedy_coloring(graph):
    colors = {}
    for node in graph.nodes():
        # Pobieramy kolory sąsiadów
        neighbor_colors = {colors[neighbor] for neighbor in graph.neighbors(node) if neighbor in colors}
        
        # Wybieramy najmniejszy dostępny kolor
        for color in range(len(graph)):
            if color not in neighbor_colors:
                colors[node] = color
                break
    return colors

# Tworzenie grafu na podstawie zadanych połączeń
def create_custom_graph():
    G = nx.Graph()
    edges = [
        ('A', 'B'),
        ('A', 'C'),
        ('B', 'D'),
        ('C', 'D'),
        ('D', 'E'),
        ('E', 'F'),
        ('F', 'A')
    ]
    G.add_edges_from(edges)
    return G

# Rysowanie grafu z kolorami i legendą
def draw_colored_graph(graph, colors):
    # Tworzymy mapowanie kolorów na nazwy
    color_map = plt.cm.tab10  # Używamy koloru tab10 z Matplotliba
    
    # Wyciągamy kolory wierzchołków
    unique_colors = sorted(set(colors.values()))
    color_legend = {color: color_map(color / len(unique_colors)) for color in unique_colors}

    # Mapujemy wierzchołki na kolory
    node_colors = [color_legend[colors[node]] for node in graph.nodes()]

    # Rysujemy graf
    pos = nx.spring_layout(graph, seed=42)  # Układ sprężynowy dla ładnego rozmieszczenia
    nx.draw(graph, pos, with_labels=True, node_color=node_colors, edge_color="gray", node_size=500, font_size=10)

    # Dodajemy legendę
    legend_handles = [plt.Line2D([0], [0], marker='o', color='w', markerfacecolor=color_legend[c], markersize=10, label=f'Kolor {c}')
                      for c in unique_colors]
    plt.legend(handles=legend_handles, loc='best', title="Użyte kolory")

    plt.show()

# Główna funkcja
if __name__ == "__main__":
    G = create_custom_graph()
    coloring = greedy_coloring(G)
    draw_colored_graph(G, coloring)
