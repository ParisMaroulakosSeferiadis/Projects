import networkx as nx
from matplotlib import pyplot as plt
import hellas_cities


G1= hellas_cities.get_cities_distances_80_graph()
nx.draw(G1, with_labels=True)
plt.show()

C1 = nx.connected_components(G1)
print(len(list(C1)))

