#include<stdio.h>
#include<time.h>
#include<stdlib.h>

// Syed Safiullah Shah 

int main()
{
    int dice1, dice2, sum;
    srand(time(0));

    do
    {
        printf("Enter your dice number: ");
        scanf_s("%d", &dice2);
        if (dice2 < 1 || dice2 > 6)
        {
            return 1;
        }
        else
        {
         dice1 = (rand() % 6) + 1;
            sum = dice1 + dice2;
            printf("\nThe sum of both dice is %d\n", sum);
        }
    } while (dice1 + dice2 != 12);
}
