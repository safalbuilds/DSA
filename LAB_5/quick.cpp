#include <iostream>

int partition(int A[], int l, int r)
{
    int pivot = A[l];
    int x = l;
    int y = r;

    while (x < y)
    {

        while (A[x] <= pivot && x <= r)
        {
            x++;
        }

        while (A[y] > pivot)
        {
            y--;
        }

        if (x < y)
            std::swap(A[x], A[y]);
    }
    std::swap(A[l], A[y]);
    return y;
}
void quickSort(int A[], int l, int r)
{
    if (l < r)
    {

        int p = partition(A, l, r);
        quickSort(A, l, p - 1);
        quickSort(A, p + 1, r);
    }
}

// int main(){
//     int A[] = {12, 3, 5, 11, 10};
//     quickSort(A, 0, 4);
//     for(int i : A){
//         std::cout << i << std::endl;
//     }
// }