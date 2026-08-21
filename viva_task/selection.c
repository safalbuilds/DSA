#include <stdio.h>

void swapp(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int pos = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[pos])
            {
                pos = j;
            }
        }
        swapp(&arr[i], &arr[pos]);
    }
}

int main()
{
    int A []= {1, 2, 0, 1, 9, -1};
    int n = sizeof(A)/ sizeof(A[0]);

    selection(A, n);
    for (int i =0; i<n;i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}