import networkx as nx
from matplotlib import pyplot as plt
import hellas_cities

G = hellas_cities.get_cities_distances_60_graph()
nx.draw(G, with_labels=True)
plt.show()

C = nx.connected_components(G)
print(len(list(C)))

import numpy as np

def gaussian_kernel( sigma=1):
    x, y = np.mgrid[288+1, 355+1]
    normal = 1 / (2.0 * np.pi * sigma**2)
    g =  np.exp(-((x**2 + y**2) / (2.0*sigma**2))) * normal
    return g
