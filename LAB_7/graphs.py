from dfs import dfs
from bfs import bfs

G = {
    1: [3, 4, 2],
    2: [1, 4, 5],
    3: [1, 4],
    4: [1, 2, 3, 5],
    5: [2, 4]
}

G1 = {
    'A': ['B', 'Q'],
    'B': ['A', 'T'],
    'Q': ['A', 'T', 'Y'],
    'T': ['B', 'Q', 'Y', 'Z'],
    'Y': ['Q', 'T', 'S'],
    'Z': ['T', 'S', 'W'],
    'S': ['Z', 'Y', 'W'],
    'W': ['Z', 'S']
}

print(dfs(G1, 'A'))
print(bfs(G1, 'A'))