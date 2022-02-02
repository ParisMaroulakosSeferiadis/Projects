import networkx as nx
G = nx.florentine_families_graph()

ed=nx.edge_betweenness_centrality(G)
print("Edge Betweenness centrality=",ed)
family_edge=[
(('Acciaiuoli', 'Medici'), 0.13333333333333336),
(('Medici', 'Barbadori'), 0.1761904761904762),
(('Medici', 'Ridolfi'), 0.146031746031746),
(('Medici', 'Tornabuoni'), 0.12222222222222222),
(('Medici', 'Albizzi'), 0.21269841269841266),
(('Medici', 'Salviati'), 0.24761904761904763),
(('Castellani', 'Peruzzi'), 0.05714285714285715),
(('Castellani', 'Strozzi'), 0.05238095238095239),
(('Castellani', 'Barbadori'), 0.11904761904761905),
(('Peruzzi', 'Strozzi'), 0.04285714285714286),
(('Peruzzi', 'Bischeri'), 0.07142857142857144),
(('Strozzi', 'Ridolfi'), 0.1365079365079365),
(('Strozzi', 'Bischeri'), 0.07936507936507937),
(('Ridolfi', 'Tornabuoni'), 0.04761904761904762),
(('Tornabuoni', 'Guadagni'), 0.12222222222222223),
(('Albizzi', 'Ginori'), 0.13333333333333336),
(('Albizzi', 'Guadagni'),0.15555555555555559),
(('Salviati', 'Pazzi') ,0.13333333333333336),
(('Bischeri', 'Guadagni') ,0.1634920634920635),
(('Guadagni', 'Lamberteschi'),0.13333333333333336)
]
e=sorted(family_edge,key=lambda family:family[1],reverse=True)
pl=max(family_edge,key=lambda family:family[1])
print("SortedEdge Betweenness centrality=",e)
print("Max Edge Betweenness centrality=",pl)