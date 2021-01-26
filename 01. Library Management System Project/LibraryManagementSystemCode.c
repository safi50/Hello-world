                                                        /*LIBRARY MANAGEMENT SYSTEM*/
/*This Project Is Made By:
Syed Safi Ullah SHah */

#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<direct.h>                     //contains _dos_getdate
#include<time.h>

#define RETURNTIME 15

char catagories[][15] = { "Computer", "Electronics", "Electrical", "Civil", "Mechanical", "Architecture" };
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void issuerecord();
void loaderanim();

//list of global files that can be acceed form anywhere in program
FILE* fp, *ft, *fs;


COORD coord = { 0, 0 };
//list of global variable
int s;
char findbook;

void gotoxy(int x, int y)
{
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct meroDate
{
	int mm, dd, yy;
};
struct books
{
	int id;
	char stname[20];
	char name[20];
	char Author[20];
	int quantity;
	float Price;
	int count;
	int rackno;
	char* cat;
	struct meroDate issued;
	struct meroDate duedate;
};
struct books a;
int main()
{
	mainmenu();
	getch();
	return 0;

}
void mainmenu()
{
	system("cls");
	//    textbackground(13);
	int i;
	printf("  \n\n\n\t\t******* LIBRARY MANAGEMENT SYSTEM *******\n\n");
	printf("  \t\t1. Add Books\n\n");
	printf("  \t\t2. Delete Books\n\n");
	printf("  \t\t3. Search Books\n\n");
	printf("  \t\t4. Issue Books\n\n");
	printf("  \t\t5. View Books List\n\n");
	printf("  \t\t6. Edit Book's Record\n\n");
	printf("  \t\t7. Close Application\n\n");
	printf("  \t\t******************************************\n\n");
	printf("  \t\tEnter your choice:");
	switch (getch())
	{
	case '1':
		addbooks();
		break;
	case '2':
		deletebooks();
		break;
	case '3':
		searchbooks();
		break;
	case '4':
		issuebooks();
		break;
	case '5':
		viewbooks();
		break;
	case '6':
		editbooks();
		break;
	case '7':
	{
				system("cls");
				printf("\n\n\n************************************************************************\n\n");
				printf("  \tThankyou for using my Software\n");
				printf("\n Project made by : Syed Safi Ullah Shah ");
				printf("************************************************************************\n");
				exit(0);
	}
	default:
	{
			   printf("\a Wrong Entry!!Please re-entered correct option");
			   if (getch())
				   mainmenu();
	}

	}
}
void addbooks(void)    //funtion that add books
{
	system("cls");
	int i;
	printf("  \n\n\n\t\t****** SELECT CATEGORIES ********\n\n");
	printf("  \t\t1. Computer\n\n");
	printf("  \t\t2. Electronics\n\n");
	printf("  \t\t3. Electrical\n\n");
	printf("  \t\t4. Civil\n\n");
	printf("  \t\t5. Mechanical\n\n");
	printf("  \t\t6. Architecture\n\n");
	printf("  \t\t7. Back to main menu\n\n");
	printf("  \t\t*********************************\n\n");
	printf("  \t\tEnter your choice:");
	scanf("%d", &s);
	if (s == 7)

		mainmenu();
	system("cls");
	fp = fopen("lib.dat", "ab+");
	if (getdata() == 1)
	{
		a.cat = catagories[s - 1];
		fseek(fp, 0, SEEK_END);
		fwrite(&a, sizeof(a), 1, fp);
		fclose(fp);
		printf("\n  \tThe Record Is Sucessfully Saved\n");
		printf("\n  \tDo you want to save more?(Y / N):");
		if (getch() == 'n')
			mainmenu();
		else
			system("cls");
		addbooks();
	}
}
void deletebooks()    //function that delete items from file fp
{
	system("cls");
	int d;
	char another = 'y';
	while (another == 'y')  //infinite loop
	{
		system("cls");
		printf("  \n\n\n\t\tEnter the Book ID to  delete:");
		scanf("%d", &d);
		fp = fopen("lib.dat", "rb+");
		rewind(fp);
		while (fread(&a, sizeof(a), 1, fp) == 1)
		{
			if (a.id == d)
			{

				printf("  \n\t\tThe Book Record Is Available\n");
				printf("  \n\t\tBook name is %s", a.name);
				printf("  Rack No. is %d", a.rackno);
				findbook = 't';
			}
		}
		if (findbook != 't')
		{
			printf("  \n\t\tNo record is found modify the search\n");
			if (getch())
				mainmenu();
		}
		if (findbook == 't')
		{
			printf("  \n\t\tDo you want to delete it?(Y/N):");
			if (getch() == 'y')
			{
				ft = fopen("test.dat", "wb+");  //temporary file for delete
				rewind(fp);
				while (fread(&a, sizeof(a), 1, fp) == 1)
				{
					if (a.id != d)
					{
						fseek(ft, 0, SEEK_CUR);
						fwrite(&a, sizeof(a), 1, ft); //write all in tempory file except that
					}                              //we want to delete
				}
				fclose(ft);
				fclose(fp);
				remove("lib.dat");
				rename("test.dat", "lib.dat"); //copy all item from temporary file to fp except that
				fp = fopen("lib.dat", "rb+");    //we want to delete
				if (findbook == 't')
				{
					printf("  \n\t\tThe Record Is Sucessfully Deleted");
					printf("  \n\t\tDelete another record?(Y/N)");
				}
			}
			else
				mainmenu();
			fflush(stdin);
			another = getch();
		}
	}
	mainmenu();
}
void searchbooks()
{
	system("cls");
	int d;
	printf("  \n\n\n\t\t*********Search Books********\n\n");
	printf("  \t\t1. Search By ID\n\n");
	printf("  \t\t2. Search By Name\n\n");
	printf("  \t\tEnter Your Choice:");
	fp = fopen("lib.dat", "rb+"); //open file for reading propose
	rewind(fp);   //move pointer at the begining of file
	switch (getch())
	{
	case '1':
	{
				system("cls");
				printf("  \n\n\n\t\t*********Search Books By Ids*********\n\n");
				printf("  \t\tEnter the book id:");
				scanf("%d", &d);
				while (fread(&a, sizeof(a), 1, fp) == 1)
				{
					if (a.id == d)
					{
						printf("\n  \t\tThe Book Is Available\n");
						printf("  \t\t****************\n");
						printf("\n  \t\tID:%d", a.id);
						printf("\n  \t\tName:%s", a.name);
						printf("\n  \t\tAuthor:%s ", a.Author);
						printf("\n  \t\tQuantity:%d ", a.quantity);
						printf("\n  \t\tPrice:Rs.%.2f", a.Price);
						printf("\n  \t\tRack No:%d\n\n", a.rackno);
						printf("  \t\t****************");
						findbook = 't';
					}

				}
				if (findbook != 't')  //checks whether conditiion enters inside loop or not
				{
					printf("\n  \t\t*************************************");
					printf("\n\n  \t\tNo Record Found");
				}
				printf("\n  \t\tTry another search?(Y/N)");
				if (getch() == 'y')
					searchbooks();
				else
					mainmenu();
				break;
	}
	case '2':
	{
				char s[15];
				system("cls");
				printf("  \n\n\t\t**************Search Books By Name***************\n");
				printf("\n  \t\tEnter Book Name:");
				scanf("%s", s);
				int d = 0;
				while (fread(&a, sizeof(a), 1, fp) == 1)
				{
					if (strcmp(a.name, (s)) == 0) //checks whether a.name is equal to s or not
					{
						printf("\n  \t\tThe Book Is Available");
						printf("\n  \t\t********************\n");
						printf("\n  \t\tID:%d", a.id);
						printf("\n  \t\tName:%s", a.name);
						printf("\n  \t\tAuthor:%s", a.Author);
						printf("\n  \t\tQantity:%d", a.quantity);
						printf("\n  \t\tPrice:Rs.%.2f", a.Price);
						printf("\n  \t\tRack No:%d ", a.rackno);
						printf("\n\n  \t\t*********************");
						d++;
					}

				}
				if (d == 0)
				{
					printf("\n\n   \t\t*************************************************");
					printf("\n  \t\tNo Record Found");
				}
				printf("\n  \t\tTry another search?(Y/N)");
				if (getch() == 'y')
					searchbooks();
				else
					mainmenu();
				break;
	}
	default:
		getch();
		searchbooks();
	}
	fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
	int t;
	SYSTEMTIME T;
	GetLocalTime(&T);
	system("cls");
	printf("\n\n\n  \t\t*******ISSUE SECTION********\n\n");
	printf("\n  \t\t1. Issue a Book\n");
	printf("\n  \t\t2. View Issued Book\n");
	printf("\n  \t\t3. Search Issued Book\n");
	printf("\n  \t\t4. Remove Issued Book\n");
	printf("\n  \t\tEnter a Choice:");
	switch (getch())
	{
	case '1':  //issue book
	{
				   system("cls");
				   int c = 0;
				   char another = 'y';
				   while (another == 'y')
				   {
					   system("cls");
					   printf("\n\n\n  \t\t*******Issue Book section*******\n\n");
					   printf("  \t\tEnter the Book Id:");
					   scanf("%d", &t);
					   fp = fopen("lib.dat", "rb");
					   fs = fopen("Issue.dat", "ab+");
					   if (checkid(t) == 0) //issues those which are present in library
					   {
						   printf("  \t\tThe Book Record Is Available!\n");
						   printf("  \t\tThere are %d unissued books in library\n ", a.quantity);
						   printf("  \t\tThe name of book is %s", a.name);
						   printf("\n  \t\tEnter student name:");
						   scanf("%s", a.stname);
						   printf("\n  \t\tIssued date= %d-%d-%d\n", T.wDay, T.wMonth, T.wYear);

						   printf("\n  \t\tThe BOOK of ID %d is issued to %s", a.id, a.stname);
						   a.issued.dd = T.wDay;
						   a.issued.mm = T.wMonth;
						   a.issued.yy = T.wYear;
						   a.duedate.dd = T.wDay + RETURNTIME;   //for return date
						   a.duedate.mm = T.wMonth;
						   a.duedate.yy = T.wYear;
						   if (a.duedate.dd > 30)
						   {
							   a.duedate.mm += a.duedate.dd / 30;
							   a.duedate.dd -= 30;

						   }
						   if (a.duedate.mm > 12)
						   {
							   a.duedate.yy += a.duedate.mm / 12;
							   a.duedate.mm -= 12;

						   }
						   printf("\n\n  \t\tTo be return:%d-%d-%d", a.duedate.dd, a.duedate.mm, a.duedate.yy);
						   fseek(fs, sizeof(a), SEEK_END);
						   fwrite(&a, sizeof(a), 1, fs);
						   fclose(fs);
						   c = 1;
					   }
					   if (c == 0)
					   {
						   printf("\n  \t\tNo record found");
					   }
					   printf("\n\n  \t\tIssue any more(Y/N):");
					   fflush(stdin);
					   another = getche();
					   printf("\n\t\t");
					   fclose(fp);
				   }

				   break;
	}
	case '2':  //show issued book list
	{
				   system("cls");
				   int j = 4;
				   printf("\n\n\n  \t\t******Issued Book List*******\n");
				   printf("\n    STUDENT NAME    ID    BOOK NAME    ISSUED DATE    RETURN DATE\n");
				   fs = fopen("Issue.dat", "rb");
				   while (fread(&a, sizeof(a), 1, fs) == 1)
				   {
					   printf("     %s    ", a.stname);
					   printf("    %d    ", a.id);
					   printf("  %s  ", a.name);
					   printf("  %d-%d-%d     ", a.issued.dd, a.issued.mm, a.issued.yy);
					   printf("  %d-%d-%d      ", a.duedate.dd, a.duedate.mm, a.duedate.yy);
					   j++;
					   printf("\n");

				   }
				   fclose(fs);
				   returnfunc();
	}
		break;
	case '3':   //search issued books by id
	{
					system("cls");
					printf("\n\n\n  \t\tEnter Book ID:");
					int p, c = 0;
					char another = 'y';
					while (another == 'y')
					{

						scanf("%d", &p);
						fs = fopen("Issue.dat", "rb");
						while (fread(&a, sizeof(a), 1, fs) == 1)
						{
							if (a.id == p)
							{
								issuerecord();
								printf("\n\n  \t\tPress any key.......");
								getch();
								issuerecord();
								c = 1;
							}

						}
						fflush(stdin);
						fclose(fs);
						if (c == 0)
						{
							printf("\n\n  \t\tNo Record Found");
						}
						printf("\n\n  \t\tTry Another Search?(Y/N)");
						another = getch();
					}
	}
		break;
	case '4':  //remove issued books from list
	{
				   system("cls");
				   int b;
				   FILE* fg;  //declaration of temporary file for delete
				   char another = 'y';
				   while (another == 'y')
				   {
					   printf("\n\n\n  \t\tEnter book id to remove:");
					   scanf("%d", &b);
					   fs = fopen("Issue.dat", "rb+");
					   while (fread(&a, sizeof(a), 1, fs) == 1)
					   {
						   if (a.id == b)
						   {
							   issuerecord();
							   findbook = 't';
						   }
						   if (findbook == 't')
						   {
							   printf("\n\n  \t\tDo You Want to Remove it?(Y/N)");
							   if (getch() == 'y')
							   {
								   fg = fopen("record.dat", "wb+");
								   rewind(fs);
								   while (fread(&a, sizeof(a), 1, fs) == 1)
								   {
									   if (a.id != b)
									   {
										   fseek(fs, 0, SEEK_CUR);
										   fwrite(&a, sizeof(a), 1, fg);
									   }
								   }
								   fclose(fs);
								   fclose(fg);
								   remove("Issue.dat");
								   rename("record.dat", "Issue.dat");
								   printf("\n\n  \t\tThe issued book is removed from list");

							   }

						   }
						   if (findbook != 't')
						   {
							   printf("\n\n  \t\tNo Record Found");
						   }
					   }
					   printf("  \n\n  \t\tDelete any more?(Y/N)");
					   another = getch();
				   }
	}
	default:
		printf("\aWrong Entry!!");
		getch();
		issuebooks();
		break;
	}
	returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
	int i = 0, j;
	system("cls");
	printf(" \t********************** Book List *************************\n\n");
	printf("         ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo ");
	j = 4;
	fp = fopen("lib.dat", "rb");
	while (fread(&a, sizeof(a), 1, fp) == 1)
	{
		
		
		printf("\n\t%d", a.id);
		
		printf("\t%s", a.name);
		
		printf("     %s", a.Author);
		
		printf("\t  %d", a.quantity);
		
		printf("\t  %.2f", a.Price);
		
		printf("    %d", a.rackno);
		j++;
		i = i + a.quantity;
	}
	
	printf("\n\n  \t\tTotal Books =%d\n", i);
	fclose(fp);
	
	returnfunc();
}
void editbooks(void)  //edit information about book
{
	system("cls");
	int c = 0;
	int d, e;
	printf("\n\n\n  \t\t******Edit Books Section******");
	char another = 'y';
	while (another == 'y')
	{
		system("cls");
		printf("\n\n  \t\tEnter Book Id to be edited:");
		scanf("%d", &d);
		fp = fopen("lib.dat", "rb+");
		while (fread(&a, sizeof(a), 1, fp) == 1)
		{
			if (checkid(d) == 0)
			{
				printf("\n  \t\tThe Book Is Available\n");
				printf("\n  \t\tThe Book ID:%d\n", a.id);
				printf("\n  \t\tEnter New Name:"); scanf("%s", a.name);
				printf("\n  \t\tEnter New Author:"); scanf("%s", a.Author);
				printf("\n  \t\tAdd New Quantity:"); scanf("%d", &a.quantity);
				printf("\n  \t\tEnter New Price:"); scanf("%f", &a.Price);
				printf("\n  \t\tEnter New RackNo:"); scanf("%d", &a.rackno);
				printf("\n\n \t\tThe record is modified\n");
				fseek(fp, ftell(fp) - sizeof(a), 0);
				fwrite(&a, sizeof(a), 1, fp);
				fclose(fp);
				c = 1;
			}
			if (c == 0)
			{
				printf("\n\n  \t\tNo record found\n");
			}
		}
		printf("\n\n  \t\tModify another Record?(Y/N)\n");
		fflush(stdin);
		another = getch();
	}
	returnfunc();
}
void returnfunc(void)
{
	{
		printf("\n  \t\tPress ENTER to return to main menu");
	}
a:
	if (getch() == 13) //allow only use of enter
		mainmenu();
	else
		goto a;
}
int getdata()
{
	int t;
	printf("\n\tEnter the Information Below\n\n");
	printf("\tCategory:");
	printf("%s\n", catagories[s - 1]);
	printf("\n\tBook ID:");
	scanf("%d", &t);
	if (checkid(t) == 0)
	{
		printf("\a\n\tThe book id already exists\a\n");
		getch();
		mainmenu();
		return 0;
	}
	a.id = t;
	printf("\n\tBook Name:");
	scanf("%s", a.name);
	printf("\n\tAuthor:");
	scanf("%s", a.Author);
	printf("\n\tQuantity:");
	scanf("%d", &a.quantity);
	printf("\n\tPrice:");
	scanf("%f", &a.Price);
	printf("\n\tRack No:"); gotoxy(30, 11);
	printf("\n\n\n\n\n\n\t\t\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%d", &a.rackno);
	return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
	rewind(fp);
	while (fread(&a, sizeof(a), 1, fp) == 1)
	if (a.id == t)
		return 0;  //returns 0 if book exits
	return 1; //return 1 if it not
}

void issuerecord()  //display issued book's information
{
	system("cls");
	printf("\n\n  \t\tThe Book has taken by Mr. %s\n", a.stname);
	printf("\n  \t\tIssued Date:%d-%d-%d", a.issued.dd, a.issued.mm, a.issued.yy);
	printf("\n\n  \t\tReturning Date:%d-%d-%d", a.duedate.dd, a.duedate.mm, a.duedate.yy);
}
//END OF PROGRAMMMMMM
