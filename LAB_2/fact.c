#include <stdio.h>

int fact(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return fact(n - 1) * n;
    }
}

int fact_tail(int n, int fact)
{
    if (n == 0 || n == 1)
    {
        return fact;
    }
    else
    {
        return fact_tail(n - 1, n * fact);
    }
}
int main()
{
    printf("%d\n", fact(5));
    printf("%d\n", fact_tail(5, 1));
}