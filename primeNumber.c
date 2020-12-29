#include<stdio.h>
/* SYED SAFIULLAH SHAH

int main()
{
    int n = 20, i = 3, count, k;

    printf("First 20 prime numbers are : \n  ");
    printf("2 ");


    for (count = 2; count <= n; i++)
    {
        for (k = 2; k < i; k++)
        {
            if (i % k == 0)
                break;
        }

        if (k == i) 
        {
            printf("%d ", i);
            count++;
        }

    }
    return 0;
}
