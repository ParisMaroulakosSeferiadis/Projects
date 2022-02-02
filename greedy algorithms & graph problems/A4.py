import networkx as nx
from matplotlib import pyplot as plt
import hellas_cities

G2 = hellas_cities.get_cities_distances_120_graph()
p = nx.single_source_dijkstra_path(G2, 'Xanthi')
path1 = p['Athina']
print(path1)

def path_length(G2, path1):
    dist = 0
    length = len(path1)
    for hop in range(length - 1):
        dist = dist + G2[path1[hop]][path1[hop + 1]]['weight']
    return dist

print(path_length(G2, path1))
