/*

Syed Safiullah Shah

                                           ATM MACHINE                 
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct acc_details
{
    char name[60];
    int pin;
    int cash;
} account;

account current_acc;

int account_no;
FILE *accounts_ptr = NULL; //file pointor for the acount details file
FILE *summary_ptr = NULL;  //file pointor for the summary file
account data_base[50];     // To store account data

time_t t;
int account_counter = 0; //counter to keep check of accounts in the data base array and control the loop and avoid extra iterations

void file_open(int a);
void file_close();       //closes all files and flushes the file pointors
void create_acc();       //function to create account
void acc_withdrawal();   //function for cash withdrawal
void acc_deposit();      //function for depositing cash in account
void acc_balance();      //function for checking balance of account
void acc_summary();      //function to show the summary of account
int acc_validation(int); //to check entered data

void get_data()
{
    accounts_ptr = fopen("Account_Details.txt", "r"); //opens file in read mode
    char filechar = fgetc(accounts_ptr);              //character to check for eof

    while ((filechar != EOF))
    {
        if (filechar == '\n')
        {

            fscanf(accounts_ptr, "\n%s %d %d", &data_base[account_counter].name, &data_base[account_counter].pin, &data_base[account_counter].cash);

            account_counter++;
        }

        filechar = fgetc(accounts_ptr);
    }
    fclose(accounts_ptr);
    fflush(accounts_ptr);
}
void put_data()
{
    accounts_ptr = fopen("Account_Details.txt", "w");
    for (int i = 0; i < account_counter; i++)
    {
        fprintf(accounts_ptr, "\n%s %d %d", data_base[i].name, data_base[i].pin, data_base[i].cash);
    }
    fclose(accounts_ptr);
    fflush(accounts_ptr);
}

//main fuction
int main()
{

    file_open(0);

    get_data();
    int choice = 6;
    time(&t);

    printf("\n1.Account Creation\n2.Balance Check\n3.Cash Withdrawl\n4.Cash Deposit\n5.Account Statement\n6.Exit\n"); //prints available options to the user

    printf("\n\7Enter Number : ");
    scanf("%d", &choice);

    file_open(5);

    while (choice != 6)
    {
        switch (choice)
        {

        case (1): //Account creation
        {
            system("cls");
            printf("\n Account Creation\t\t\t\t %s\n", ctime(&t));
            create_acc();
            printf("\nPress Any Key To Continue");
            getchar();
            getchar();
            break;
        }

        case (2): //Balance Check
        {
            system("cls");
            printf("\n Balance Check\t\t\t\t %s\n", ctime(&t));
            acc_balance();
            printf("\nPress Any Key To Continue");
            getchar();
            getchar();
            break;
        }
        case (3): //Cash Withdrawl
        {
            system("cls");
            printf("\n Cash Withdrawl\t\t\t\t %s\n", ctime(&t));
            acc_withdrawal();
            printf("\nPress Any Key To Continue");
            getchar();
            getchar();
            break;
        }
        case (4): //Cash deposit
        {
            system("cls");
            printf("\n Cash Deposit\t\t\t\t %s\n", ctime(&t));
            acc_deposit();
            printf("\nPress Any Key To Continue");
            getchar();
            getchar();
            break;
        }

        case (5): //Account Statement
        {
            system("cls");
            printf("\n Account Statement\t\t\t\t %s\n", ctime(&t));
            acc_summary();
            printf("\nPress Any Key To Continue");
            getchar();
            getchar();
            break;
        }

        default:
        {

            printf("\n Wrong Input. Try again.");
            printf("\n\7Press any key to retry ");

            break;
        }
        }

        system("cls");
        time(&t);
        printf("\n ATM\t\t %s\n", ctime(&t));
        printf("\n1.Account Creation\n2.Balance Check\n3.Cash Withdrawl\n4.Cash Deposit\n5.Account Statement\n6.Exit\n");

        printf("\n\7Enter Choice : ");
        scanf("%d", &choice);
    }
    put_data();
    file_close();

    return 0;
}

void file_open(int a)
{
    if (a == 0)
    {
        accounts_ptr = fopen("Account_Details.txt", "a+");
        if (accounts_ptr == NULL)
        {
            printf("Error Opening Accounts File");
        }
        summary_ptr = fopen("Summary.txt", "a+");
        if (summary_ptr == NULL)
        {
            printf("Error ");
        }
        file_close();
    }
    else
    {
        summary_ptr = fopen("Summary.txt", "a+");

        summary_ptr = fopen("Summary.txt", "a+");
        if (summary_ptr == NULL)
        {
            printf("Error ");
        }
    }
}

void file_close()
{

    fclose(accounts_ptr);
    fflush(accounts_ptr);
    fclose(summary_ptr);
    fflush(summary_ptr);
}

int acc_validation(int type)
{
    int flag = 0;
    int i = 0;
    for (i = 0; i <= account_counter; i++)
    {
        if (strcmp(current_acc.name, data_base[i].name) == 0)
        {
            flag++;
            break;
        }
    }
    if ((flag > 0) && (type == 2))
    {
        current_acc = data_base[i];
        account_no = i;
    }

    return flag;
}

void create_acc()
{
    printf("\n User name should be :\n\n 1.Case Sensitive\t\t 2.Should not contain spaces.\n\n");
    printf("\nEnter Username : ");
    scanf("%s", &current_acc.name);
    while (acc_validation(1) != 0)
    {
        printf("\nTry Again \n");
        printf("\nEnter UserName: ");
        scanf("%s", &current_acc.name);
    }

    printf("\nUsername can be used.");
    file_close();
    file_open(1);
    printf("\n Enter Pin: ");
    scanf("%d", &current_acc.pin);
    printf("\n Input Cash: ");
    scanf("%d", &current_acc.cash);
    while (current_acc.cash % 500 != 0)
    {
        printf("\nPlease Enter a multiple of 500\n");
        printf("\n Input Cash: ");
        scanf("%d", &current_acc.cash);
    }

    data_base[account_counter] = current_acc;
    account_counter++;
    printf("\nAccount Created Sucessfully\n");
    fprintf(summary_ptr, "\n %s Type : Account Creation  Amount: %d  Time: %s  \n", current_acc.name, current_acc.cash, ctime(&t));
    file_close();
}

void acc_withdrawal()
{
    int pin_counter = 1;
    int temp_pin = NULL;
    int withdraw_amount = 0;
    printf("\nEnter Username :");
    scanf("%s", current_acc.name);

    while (acc_validation(2) == 0)
    {
        printf("\nUser Not found\n");
        printf("\nEnter UserName: ");
        scanf("%s", &current_acc.name);
    }

    while ((current_acc.pin != temp_pin) && (pin_counter <= 3))
    {
        printf("\n 3 tries allowed for Pin,\nThis is try %d.\n", pin_counter);
        printf("\nEnter Pin : ");
        scanf("%d", &temp_pin);
        pin_counter++;
    }

    if ((current_acc.pin == temp_pin) && (pin_counter <= 3))
    {
        printf("\nBalance: %d ", current_acc.cash);
        printf("\nEnter withdraw amount: ");
        scanf("%d", &withdraw_amount);

        while ((withdraw_amount > current_acc.cash) || (current_acc.cash % 500 != 0))
        {
            while (current_acc.cash % 500 != 0)
            {
                printf("\nPlease Enter a multiple of 500\n");
                printf("\nEnter withdraw amount: ");
                scanf("%d", &withdraw_amount);
            }
            if (withdraw_amount > current_acc.cash)
            {
                printf("\nNot Enough balance");
                printf("\nTry Again or Enter 0");
                printf("\nEnter withdraw amount: ");
                scanf("%d", &withdraw_amount);
            }
        }

        current_acc.cash = (current_acc.cash - withdraw_amount);
        data_base[account_no] = current_acc;
        printf("\nRemaining Balance : %d\n", current_acc.cash);
        printf("\a\nCollect Your Cash\n");
        printf("\a\nThank You.\n");

        file_open(1);
        fprintf(summary_ptr, "\n %s Type : Withdrawl  Amount: %d Balance: %d Time: %s  \n", current_acc.name, withdraw_amount, current_acc.cash, ctime(&t));
        file_close();
    }
}

void acc_deposit()
{

    int pin_counter = 1;
    int temp_pin = NULL;
    int deposit_amount = 0;

    printf("\nEnter Username :");
    scanf("%s", current_acc.name);
    while (acc_validation(2) == 0)
    {
        printf("\nUser Not found\n");
        printf("\nEnter UserName: ");
        scanf("%s", &current_acc.name);
    }

    while ((current_acc.pin != temp_pin) && (pin_counter <= 3))
    {
        printf("\n3 tries allowed for Pin.\nThis is try %d.\n", pin_counter);
        printf("\nEnter Pin : ");
        scanf("%d", &temp_pin);
        pin_counter++;
    }
    if ((current_acc.pin == temp_pin) && (pin_counter <= 3))
    {
        printf("\nBalance: %d ", current_acc.cash);

        printf("\nEnter deposit amount: ");
        scanf("%d", &deposit_amount);

        while (current_acc.cash % 500 != 0)
        {
            printf("\nPlease Enter a multiple of 500\n");
            printf("\nEnter withdraw amount: ");
            scanf("%d", &deposit_amount);
        }

        current_acc.cash = (current_acc.cash + deposit_amount);
        data_base[account_no] = current_acc;
        printf("\nNew Balance : %d\n", current_acc.cash);
        printf("\a\nThanks For Your vist.\n");

        file_open(3);
        fprintf(summary_ptr, "\n %s Type : Deposit  Amount: %d Balance: %d Time: %s  \n", current_acc.name, deposit_amount, current_acc.cash, ctime(&t));
        file_close();
    }
}
void acc_balance()
{
    int pin_counter = 1;
    int temp_pin = NULL;

    printf("\nEnter Username :");
    scanf("%s", current_acc.name);
    while (acc_validation(2) == 0)
    {
        printf("\nUser Not found\n");
        printf("\nEnter UserName: ");
        scanf("%s", &current_acc.name);
    }

    while ((current_acc.pin != temp_pin) && (pin_counter <= 3))
    {
        printf("\nThis is try %d. 3 tries allowed for Pin\n", pin_counter);
        printf("\nEnter Pin : ");
        scanf("%d", &temp_pin);
        pin_counter++;
    }
    if ((current_acc.pin == temp_pin) && (pin_counter <= 3))
    {
        printf("\nBalance: %d ", current_acc.cash);
    }
    printf("\a\nThanks For Your vist.\n");
}
void acc_summary()
{
    int pin_counter = 1;
    int temp_pin = NULL;
    account temp;
    printf("\nEnter Username :");
    scanf("%s", current_acc.name);
    while (acc_validation(2) == 0)
    {
        printf("\nUser Not found\n");
        printf("\nEnter UserName: ");
        scanf("%s", &current_acc.name);
    }
    while ((current_acc.pin != temp_pin) && (pin_counter <= 3))
    {
        printf("\nThis is try %d. 3 tries allowed for Pin\n", pin_counter);
        printf("\nEnter Pin : ");
        scanf("%d", &temp_pin);
        pin_counter++;
    }
    if ((current_acc.pin == temp_pin) && (pin_counter <= 3))
    {
        file_close();
        file_open(2);

        printf("\n Account Summary.\n\n");

        char filechar = fgetc(summary_ptr);

        while ((filechar != EOF))
        {

            if (filechar == '\n')
            {
                char data[500] = {0};
                strcpy(temp.name, "                      ");
                fscanf(summary_ptr, "%s", &temp.name);

                if (strcmp(temp.name, current_acc.name) == 0)
                {
                    fgets(data, 499, summary_ptr);
                    printf("\n%s", data);
                }
            }
            filechar = fgetc(summary_ptr);
        }
    }
    file_close();
    printf("\a\nThank You for using my ATM\n");
}
