#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*                --------------------Made By : Syed Safiullah Shah-------------------- */

char player1[20];
char player2[10] = "Computer";

int generateRandomNumber()
{
    int num;
    srand(time(NULL)); //srand takes seed as an input and is defined inside stdlib.h
    num = rand() % 3;
    return num;
}
int game(int x, int y);

int main()
{
    char opt1[10];
    char opt2[10];
    int num = generateRandomNumber();
    int len1, len2, i;
    if (num == 0)
    {
        opt2 == strcpy(opt2, "rock");
    }
    else if (num == 1)
    {
        opt2 == strcpy(opt2, "paper");
    }
    else
    {
        opt2 == strcpy(opt2, "scissors");
    }

    printf("Enter player 1 name : ");
    scanf("%s", &player1);
    getchar();

    for (i = 0; i < 3; i++)
    {
        printf("\t\t\t\t---------------------GAME BEGINS-------------------------\n");
        printf("\t\t\t\t---------------------BEST OF THREE!-----------------------\n");
        printf("\t\t-----------------------------------------------------------------------------------------");
        printf("\nChoose between ROCK , PAPER, OR SCISSORS\n");
        printf("ENTER CHOICE!\n\n");

        printf("%s : ", player1);
        scanf("%s", opt1);
        getchar();
        printf("%s: %s\n", player2, opt2);
        len1 = strlen(opt1);
        len2 = strlen(opt2);
        game(len1, len2);
    }

    return 0;
}

int game(int x, int y)
{

    if (x == y)
    {
        printf("\t\t\t\t\t-------------------MATCH TIED!--------------------\n");
    }
    if ((x == 4) && (y == 8))
    {
        printf("\t\t\t\t\t----------%s WINS!!!----------\n", player1);
    }
    else if ((x == 4) && (y == 5))
    {
        printf("\t\t\t\t\t----------%s WINS!!!----------\n", player2);
    }
    else if ((x == 5) && (y == 4))
    {
        printf("\t\t\t\t\t----------%s WINS!!!----------\n", player1);
    }
    else if ((x == 5) && (y == 8))
    {
        printf("\t\t\t\t\t----------%s WINS!!!----------\n", player2);
    }
    else if ((x == 8) && (y == 4))
    {
        printf("\t\t\t\t\t----------%s WINS!!!----------\n", player2);
    }
    else if ((x == 8) && (y == 5))
    {
        printf("\t\t\t\t\t----------%s WINS!!!----------\n", player1);
    }
}
