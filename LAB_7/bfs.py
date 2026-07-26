def bfs(G, start):
    queue = [start]
    visited = []

    while queue:
        vertex = queue.pop(0)
        if vertex not in visited:
            visited.append(vertex)

            for neighbour in G[vertex]:
                if neighbour not in queue and neighbour not in visited:
                    queue.append(neighbour)
    return visited
