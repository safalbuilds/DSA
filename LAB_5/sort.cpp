#include <iostream>
#include <functional>
#include <vector>
#include <chrono>
#include <fstream>
#include "merge.cpp"
#include "quick.cpp"
#include "heap.cpp"
#include "shell.cpp"
#include "radix.cpp"

#define MAX 10000

void generate_csv(
    const std::string &file,
    std::function<void(int A[], int l, int r)> sort_func)
{
    std::vector<int> arr;
    std::vector<int> numbers;
    std::vector<int> timee;
    for (int i = 1; i <= MAX; i += 100)
    {
        std::vector<int> arr = {};
        for (int j = 0; j < i; j++)
        {
            arr.push_back(random() % MAX);
        }
        int l = 0;
        int r = arr.size() - 1;
        int* A = arr.data();
        auto start = std::chrono::steady_clock::now();
        sort_func(A, l, r);
        auto end = std::chrono::steady_clock::now();
        auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        numbers.push_back(arr.size());
        timee.push_back(time_taken.count());
    }
    std::ofstream csv(file);
    csv << "number,timetaken\n";
    for (auto i = 0; i < numbers.size(); i++)
    {
        csv << numbers[i] << ',' << timee[i] << "\n";
    }
    csv.close();
    std::cout << file << " written completed" << std::endl;
}

int main(){
    generate_csv("data/merge.csv", mergeSort);
    generate_csv("data/quick.csv", quickSort);
    generate_csv("data/heap.csv", heapSort);
    generate_csv("data/shell.csv", shellSort);
    generate_csv("data/radix.csv", radixSort);
}
