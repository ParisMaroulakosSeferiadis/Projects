import networkx as nx
from matplotlib import pyplot as plt
import hellas_cities

G2 = hellas_cities.get_cities_distances_120_graph()
T = nx.tree.minimum_spanning_tree(G2, algorithm='kruskal')
nx.draw_networkx(T, with_labels=True)
plt.show()


# Draw the edges of the minimum spanning tree with red color
pos = nx.spring_layout(G2)
edge_list = list(T.edges())
nx.draw_networkx_edges(G2, pos, T.edges, edge_color='r')
nx.draw_networkx_labels(G2, pos)
plt.show()


