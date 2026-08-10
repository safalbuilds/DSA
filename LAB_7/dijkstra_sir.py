
inf = float('inf')
G = {
    'A': {'S':1, 'M':2},
    'M': {'A':2, 'S':3, 'U':1, 'Z':1},
    'S': {'M':3, 'U':7, 'A':1},
    'U': {'S':7, 'M':1, 'Z':3, 'W': 1},
    'Z': {'M':1, 'U':3, 'W':4},
    'W': {'U':1, 'Z':4}
}

def initialize(G, start):
    cost = {}
    prev = {}

    for i in G.keys():
        cost[i] = inf
        prev[i] = None

    cost[start] = 0
    return cost, prev

def relax(u, v, G, cost, prev):
    if cost[v] > cost[u] + G[u][v]:
        cost[v] = cost[u] + G[u][v]
        prev[v] = u
    return cost, prev

def djikstra(G, start):
    cost, prev = initialize(G, start)
    visited = set()
    PQ = {}
    for _ in G.keys():
        PQ[_] = cost[_]

    while(PQ):
        current = min(PQ, key=PQ.get)
        del PQ[current]
        visited.add(current)

        for neighbour in G[current].keys():
            if neighbour not in visited:
                old_cost = cost[neighbour]
                cost, prev = relax(current, neighbour, G, cost, prev)

                if old_cost > cost[neighbour]:
                    PQ[neighbour] = cost[neighbour]

    return cost, prev

def construct_path(previous, vertex):
    path = [vertex]
    print(previous)
    while previous[vertex] != None:
        path.append(previous[vertex])
        vertex = previous[vertex]

    return "->".join(path[::-1])

start = 'A'
cost, prev = djikstra(G, start)
for _ in G.keys():
    print(f"Shortest path form {start} to {_} is {construct_path(prev, _)}|cost:{cost[_]}")