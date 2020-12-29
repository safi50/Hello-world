CODE:
#include<stdio.h>
int prime(int);

int main()
{
    int x, result;
    printf(" Enter a number: ");
    scanf_s("%d", &x);

    result = prime(x);

    if (result == 1)
    {
        printf("\nThe number is prime\n");
    }
    else if (result == 0)
    {
        printf("The number is not prime\n");
    }
    else
        printf("some error occured\n");
    return 0;
}

int prime(x)
{
    int num = 0;
    for (int i = 1; i <= x; i++)
    {
        if (x % i == 0)
        {
            num++;
        }
    }
    if (num == 2)
    {
        return 1;
    }
    else
        return 0;

}


