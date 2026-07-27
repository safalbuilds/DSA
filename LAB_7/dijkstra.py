import json

inf = float('inf')

G = [
    [0, 2, 6, 4, inf],
    [2, 0, 5, inf, inf],
    [6, 5, 0, 7, 3],
    [4, inf, 7, 0, 8],
    [inf, inf, 3, 8, 0]
]

def initialize(G):
    Table = {}
    for i, _ in enumerate(G):
        Table[i+1] = {
            "cost": inf,
            "previous": None
        }
    return Table

def dijkstra(G, start):
    table = initialize(G)
    not_visited = [i for i in table.keys()]
    table[start]["cost"] = 0

    while not_visited: 
        row = min(not_visited, key=lambda x: table[x]["cost"])
        i = row - 1

        adjacent = []
        for index, weight in enumerate(G[i]):
            if weight > 0 and weight < inf:
                adjacent.append(index+1)

        for j in adjacent:
            new = min(table[j]["cost"], table[row]["cost"] + G[i][j-1] )
            if new != table[j]["cost"]:
                table[j]["previous"] = row
                table[j]["cost"] = new

        not_visited.remove(row)

    return table

data = json.dumps(dijkstra(G, 1), indent=2)
print(data)