import networkx as nx

linha = input()
G = nx.Graph()

while linha != "":
    nome1, nome2 = linha.split(" ")
    G.add_node(nome1, bipartite = 0)
    G.add_node(nome2, bipartite = 1)
    G.add_edge(nome1, nome2)
    linha = input()

numCasamentos = 1
for (node, val) in G.degree():
    if val != 2:
        M = nx.maximal_matching(G)
        numCasamentos = len(M)

print(numCasamentos)
