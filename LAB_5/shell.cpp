#include <iostream>

void shellSort(int arr[], int l, int r)
{
    int n = r - l + 1;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
// int main()
// {
//     int arr [] = {11, 10, 23, 51, -1, 0};
//     shellSort(arr, 0, 5);
//     for(int i: arr){
//         std::cout << i << " ";
//     }
// }