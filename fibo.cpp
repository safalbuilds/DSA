#include <iostream>
#include <vector>
#include <ctime>

std::vector<int> memo = {1, 1};

int fibo(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        return fibo(n - 1) + fibo(n - 2);
    }
}
int fibo_memo(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        if (n - 1 >= memo.size())
        {
            memo.push_back(fibo_memo(n - 1) + fibo_memo(n - 2));
        }
        return memo[n - 1];
    }
}

int main()
{
    int num = 45;
    std::time_t result = std::time(nullptr);
    std::cout << fibo(num) << std::endl;
    std::time_t result1 = std::time(nullptr);
    std::cout << result1 - result << " secs" << std::endl;

    result = std::time(nullptr);
    std::cout << fibo_memo(num) << std::endl;
    result1 = std::time(nullptr);
    std::cout << result1 - result << " secs";

}
