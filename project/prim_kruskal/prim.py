inf = float('inf')

G = [[0, 2, 6, 4, inf],
     [2, 0, 5, inf, inf],
     [6, 5, 0, 7, 3],
     [4, inf, 7, 0, 8],
     [inf, inf, 3, 8, 0]]

def prim(G, start):
    visited = [start]
    mst = [[0]*len(G) for _ in range(len(G))]
    while len(G) > len(visited):
        min = inf
        for vertex in visited:
            for i, weight in enumerate(G[vertex-1]):
                if i+1 not in visited and weight < min:
                    min = weight
                    parent = vertex
                    neighbour = i + 1
        visited.append(neighbour)
        mst[parent-1][neighbour-1] = min
        mst[neighbour-1][parent-1] = min
    return(mst)