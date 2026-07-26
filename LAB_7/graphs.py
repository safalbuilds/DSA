from dfs import dfs
from bfs import bfs

G = {
    1: [3, 4, 2],
    2: [1, 4, 5],
    3: [1, 4],
    4: [1, 2, 3, 5],
    5: [2, 4]
}

print(dfs(G, 1))
print(bfs(G, 1))