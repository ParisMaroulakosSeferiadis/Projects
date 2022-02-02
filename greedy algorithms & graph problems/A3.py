import networkx as nx
from matplotlib import pyplot as plt
import hellas_cities

# graph with edges of length at most 120km
G2 = hellas_cities.get_cities_distances_120_graph()
nx.draw(G2, with_labels=True)
plt.show()

C2 = nx.connected_components(G2)
print(len(list(C2)))

