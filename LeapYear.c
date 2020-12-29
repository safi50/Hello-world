#include<stdio.h>

int leapyr(int);

int main()
{

	int year = 0;
	if (leapyr(year) == 1)
	{
		printf("\nThis is a leap year");
	}
	else 
	{
		printf("\nThis is not a leap year");
	}


	return 0;
}

int leapyr(int var)
{
	int year;
	printf("Enter the year: ");
	scanf_s("%d", &year);
	if ((year % 4 == 0) && (year % 100 == 0) || (year % 400 != 0))
	{
		year = 1;
	}
	else
	{
		year = 0;
	}
	return year;
}



