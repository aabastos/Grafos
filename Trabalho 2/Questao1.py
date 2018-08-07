import networkx as nx
import math as m
import matplotlib.pyplot as plt

C = int(input())

for i in range(0, C):
    n = int(input())

    G = nx.Graph()

    if n <= 500:
        for j in range(0, n):
            linha = input()
            x, y = linha.split(" ")
            G.add_node(j, x = int(x), y = int(y))

        aux1 = 0
        aux2 = 1

        for j in range(0, int((n*(n-1))/2)):
            x1 = G.node[aux1]['x']
            y1 = G .node[aux1]['y']
            x2 = G.node[aux2]['x']
            y2 = G.node[aux2]['y']

            dist = m.sqrt(m.pow(x1 - x2, 2) + m.pow(y1 - y2, 2))

            G.add_edge(aux1, aux2, weight = dist)

            aux2 = aux2 + 1
            if aux2 == n:
                aux1 = aux1 + 1
                aux2 = aux1 + 1

        T = nx.minimum_spanning_tree(G, weight = 'weight')

        distTotal = 0
        for (u, v, wt) in T.edges.data('weight'):
            distTotal = distTotal + wt

        distTotal = distTotal / 100

        print("%.2f" %(distTotal))
