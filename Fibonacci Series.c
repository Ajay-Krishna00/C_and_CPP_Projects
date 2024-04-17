// Progarm to print Fibonacci series
#include <stdio.h>
int Fibonacci(int n) // User Defined Function
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }
}
int main()
{
    int n;
    printf("Enter upto which term of the Fibonacci series to print\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", Fibonacci(i));
    }
}