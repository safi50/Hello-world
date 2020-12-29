#include<stdio.h>

int main()
{
    int i = 1, fact = 1;
    int n;
    printf("Enter a number: ");
    scanf_s("%d", &n);

    while (i <= n)
    {
        fact = (fact * i);
        i++;

    }
    printf("The factorial of %d is %d", n, fact);

}
