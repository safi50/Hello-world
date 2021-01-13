#include<stdio.h>
int main()
{

    int column, row, x = 0;
    int a[5][5];
    printf(" Input size of square matrix:");
    scanf_s("%d", &row);
    column = row;

    printf("\n Enter the entries of the %dx%d matrix\n", row, column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("The entry for %dx%d :", i + 1, j + 1);
            scanf_s("%d", &a[i][j]);
        }
    }

    printf("\nThe matrix is:\n");
    for (int k = 0; k < row; k++)
    {
        for (int l = 0; l < column; l++)
        {
            printf("\t%d", a[k][l]);
        }
        printf("\n");
    }



    for (int k = 0; k < column; k++)
    {
        for (int l = 0; l < row; l++)
        {
            if (k == l)
            {
                x = x + a[k][l];
            }
        }
    }
    printf("\nThe sum of diagonals of  matrix is:\n%d", x);
    return 0;
}


