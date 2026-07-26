def dfs(G, start):
    stack = [start]
    visited = []

    while stack:
        vertex = stack.pop()
        if vertex not in visited:
            visited.append(vertex)

            for neighbour in G[vertex]:
                if neighbour not in stack and neighbour not in visited:
                    stack.append(neighbour)
    return visited
