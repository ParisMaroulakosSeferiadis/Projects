import networkx as nx
G = nx.florentine_families_graph()

d=nx.pagerank(G)

print("Pagerank centrality=",d)

family_pagerank=[
 ('Acciaiuoli',0.03065721480230426),
 ('Medici',0.14581844065218275),
 ('Castellani',0.06933028447008721),
 ('Peruzzi',0.06787531774407572),
 ('Strozzi',0.08809849082725613),
 ('Barbadori',0.050300712744633685),
 ('Ridolfi',0.069574170990148),
 ('Tornabuoni',0.07127928374676082),
 ('Albizzi',0.079121502380729),
 ('Salviati',0.061302640987807314),
 ('Pazzi', 0.036054222996734095),
 ('Bischeri',0.0688615381141211),
 ('Guadagni',0.09839859717156552),
 ('Ginori',0.032418257716596434),
 ('Lamberteschi',0.03090932465499793),
]
kl=sorted(family_pagerank,key=lambda family:family[1],reverse=True)

ls=max( family_pagerank ,key=lambda family:family[1])

print("Sorted Pagerank centrality=",kl)
print("Max Pagerank centrality=",ls)