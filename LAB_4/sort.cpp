#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <functional>
#include "bubble.cpp"
#include "insert.cpp"
#include "select.cpp"

#define MAX 10000

void generate_csv(
    const std::string &file,
    std::function<std::vector<int>(std::vector<int>)> sort_func)
{

    std::vector<int> numbers;
    std::vector<long long> timee;
    for (int i = 1; i <= MAX; i += 100)
    {
        std::vector<int> arr = {};
        for (int j = 0; j < i; j++)
        {
            arr.push_back(random() % MAX);
        }
        auto start = std::chrono::steady_clock::now();
        auto sorted = sort_func(arr);
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

int main()
{
    generate_csv("data/bubble.csv", Bubblee);
    generate_csv("data/insertion.csv", Insertion);
    generate_csv("data/selection.csv", Selection);
}

// int main()
// {
//     std::vector<int> arr;
//     for (int i = 0; i <= 30; i++)
//     {
//         arr.push_back(random() % 30);
//         std::cout << i << std::endl;
//     }
//     auto start = std::chrono::steady_clock::now();
//     auto sorted = Selection(arr);
//     auto end = std::chrono::steady_clock::now();
//     std::cout << "Sorted on " << end - start << std::endl;;
// }

// bubble, insertion, selection
