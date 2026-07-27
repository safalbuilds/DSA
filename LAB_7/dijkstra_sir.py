
inf = float('inf')
G = {
    'A': {'B':2, 'C':6, 'D':4},
    'B': {'A':2, 'C':6},
    'C': {'A':6, 'B':5, 'D':7, 'E':3},
    'D': {'A':4, 'C':7, 'E':8},
    'E': {'C':3, 'D':8}
}

def initialize(G, start):
    cost = {}
    prev = {}

    for i in G.keys():
        cost[i] = inf
        prev[i] = None

    cost[start] = 0
    return cost, prev

def djikstra(G, start):
    cost, prev = initialize(G, start)
    vertices = [i for i in G.keys()]
    visited = []
    print(vertices)

    while len(vertices) < len(visited):
        

djikstra(G, 'A')