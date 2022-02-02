import networkx as nx
from matplotlib import pyplot as plt


G = nx.florentine_families_graph()

nx.draw(G, with_labels=True)
plt.show()


G.add_edge('Pazzi','Strozzi')
G.add_edge('Pazzi','Albizzi')
G.add_edge('Pazzi','Acciaiuoli')
G.add_edge('Pazzi','Lamberteschi')
G.add_edge('Pazzi','Ginori')

nx.draw(G, with_labels=True)
plt.show()


b=nx.betweenness_centrality(G)

print(b)