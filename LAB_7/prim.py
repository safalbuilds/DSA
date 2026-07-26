def prim(G, start):
    T = [start]
    E = 0
    mst = []

    while len(T) < len(G):
        min = float('inf')
        for vertex in T:
            for neighbour, weight in G[vertex]:

                if neighbour not in T and min > weight:
                    min = weight
                    E = neighbour
                    V = vertex
        T.append(E)
        mst.append([V, E, min])

    return (mst)



G = {
    'A': [('B', 2), ('C', 6), ('D', 4)],
    'B': [('A', 2), ('C', 5)],
    'C': [('A', 6), ('B', 5), ('D', 7), ('E', 3)],
    'D': [('A', 4), ('C', 7), ('E', 8)],
    'E': [('C', 3), ('D', 8)]
}

print(prim(G, 'A'))
