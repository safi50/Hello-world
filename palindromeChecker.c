#include<stdio.h>
int reverser(int);
int lastdigit(int);
int Palindrome(int);
int main()
{
	int num,palindrome=1;
	printf("Enter the number: ");
	scanf_s("%d", &num);

	if (Palindrome(num) == 1)
	{
		printf("This number is a palindrome.");
	}

	else
	{
		printf("This number is not a plindrome.");
	}

	return 0;
}

int reverser(int num)
{
	int reverser = 0;
	for (; num != 0; num = num / 10)
	{
		reverser = reverser * 10 + lastdigit(num);
	}
	return reverser;
}

int lastdigit(int num)
{
	int last_digit;
	last_digit = num % 10;
	return last_digit;
}


int Palindrome(int num)
{
	int palindrome;
	if (num == reverser(num))
	{
		palindrome = 1;
	}

	else
	{
		palindrome = 0;
	}
	return palindrome;
}

