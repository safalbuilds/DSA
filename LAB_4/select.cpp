#include <iostream>
#include <vector>

std::vector<int> Selection(std::vector<int> A)
{
    int n = A.size();
    for (int i = 0; i < n - 1; i++)
    {
        int pos = i;
        for (int j = i + 1; j < n; j++)
        {
            if (A[j] < A[pos])
            {
                pos = j;
            }
        }
        std::swap(A[i], A[pos]);
    }
    return A;
}