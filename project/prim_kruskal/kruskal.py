inf = float('inf')

G = [[0, 2, 6, 4, inf],
     [2, 0, 5, inf, inf],
     [6, 5, 0, 7, 3],
     [4, inf, 7, 0, 8],
     [inf, inf, 3, 8, 0]]


def kruskal(G, start):
    pq = []
    mst = [[0]*len(G) for _ in range(len(G))]
    for i, path in enumerate(G):
        for j, weight in enumerate(path):
            if i< j and weight != inf:
                pq.append((i+1, j+1, weight))

    pq.sort(key= lambda x: x[2])

    component = list(range(len(G)))

    for u, v, weight in pq:

        # Check for cycle
        if component[u-1] == component[v-1]:
            continue

        # No cycle, so add edge
        mst[u-1][v-1]= weight
        mst[v-1][u-1]= weight

        # Merge components
        old = component[v-1]
        new = component[u-1]

        for i in range(len(component)):
            if component[i] == old:
                component[i] = new


    return(mst)

kruskal(G, 1)