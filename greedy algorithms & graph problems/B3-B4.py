import networkx as nx

G = nx.florentine_families_graph()

b=nx.betweenness_centrality(G)

print("betweenness centrality=" ,b)

family_betweenness=[
 ('Acciaiuoli',0.0),
 ('Medici',0.521978021978022),
 ('Castellani',0.05494505494505495),
 ('Peruzzi',0.02197802197802198),
 ('Strozzi',0.10256410256410257),
 ('Barbadori',0.09340659340659341),
 ('Ridolfi',0.11355311355311355),
 ('Tornabuoni',0.09157509157509157),
 ('Albizzi',0.21245421245421245),
 ('Salviati',0.14285714285714288),
 ('Pazzi', 0.0),
 ('Bischeri',0.1043956043956044),
 ('Guadagni',0.2545787545787546),
 ('Ginori',0.0),
 ('Lamberteschi',0.0),
]
k=sorted(family_betweenness,key=lambda family:family[1],reverse=True)
print("sorted betweenness centrality=",k)
l=max( family_betweenness ,key=lambda family:family[1])
print("max betweenness centrality=",l)