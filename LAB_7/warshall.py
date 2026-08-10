import copy
M = [
    [0, 1, 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1],
    [0, 0, 0, 0],
]
def warshall(M):
    W = copy.deepcopy(M)
    n = len(M)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                W[i][j] = W[i][j] or (W[i][k] and W[k][j])

    return(W)


print(warshall(M))