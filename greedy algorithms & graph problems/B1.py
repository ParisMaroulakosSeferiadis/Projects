import networkx as nx
from matplotlib import pyplot as plt

G = nx.florentine_families_graph()

nx.draw(G, with_labels=True)
plt.show()