#include<stdio.h>
//Safiullah 

int main()
{
    int column, row;
    int a[5][5];
    printf(" Enter rows of matrix: ");
    scanf_s("%d", &row);
    printf(" Enter columns of matrix:");
    scanf_s("%d", &column);

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

    printf("\nThe transpose of matrix is: \n");

    for (int k = 0; k < column; k++)
    {
        for (int l = 0; l < row; l++)
        {
            printf("\t%d", a[l][k]);
        }
        printf("\n");
    }
    return 0;
}
