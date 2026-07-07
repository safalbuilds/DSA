#include <iostream>
#include <vector>

std::vector<int> Bubblee(std::vector<int> A)
{
    for (int i = 0; i < A.size() - 1; i++)
    {
        for (int j = 0; j < A.size() - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                std::swap(A[j], A[j + 1]);
            }
        }
    }
    return A;
}