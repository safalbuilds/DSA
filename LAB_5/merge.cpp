#include <iostream>

void merge(int A[], int l, int r, int m)
{
    int i = l;
    int j = m;
    int k = l;

    int B[100000];

    while (i < m && j <= r)
    {
        if (A[i] <= A[j])
        B[k++] = A[i++];
        
        else
        B[k++] = A[j++];
    }

    for (; i < m;)
    {
        B[k++] = A[i++];
    }

    for (; j <= r; j)
    {
        B[k++] = A[j++];
    }

    for (i = l; i <= r; i++)
    {
        A[i] = B[i];
    }
}

void mergeSort(int A[], int l, int r)
{
    int m;
    if (l < r)
    {
        m = (l + r) / 2;
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, r, m + 1);
    }
}

int main(){
    int A[] = {10, -1, 0, 7, 3, 3, 9, 0};
    mergeSort(A, 0, 7);
    for(int i : A){
        std::cout << i << " ";
    }

}