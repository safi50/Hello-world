/*SYED SAFIULLAH SHAH
* 356189 BSCS10-C
*/
#include <stdio.h>
int main()
{
    int rows, i, j;
    do
    {
        printf(" Enter odd number of rows: ");
        scanf_s("%d", &rows);

    } while (rows % 2 == 0);

    for (j = 1; j <= rows / 2 + 1; j++)
    {
        for (i = 1; i <= rows - j; i++)
            printf(" ");

        for (i = 1; i <= 2 * j - 1; i++)

            printf("*");

        printf("\n");
    }
    for (j; j <= rows; j++)
    {
        for (i = 1; i < j; i++)
        {
            printf(" ");
        }
        for (i = 0; i <= 2 * (rows - j); i++)
        {
            printf("*");
        }

        printf("\n");

    }
    return 0;
}

