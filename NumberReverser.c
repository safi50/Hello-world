#include<stdio.h>
int reverse(int);
int lastdigit(int);
int Sum(int);
int main()
{
	int num;
	printf("Enter the number: ");
	scanf_s("%d", &num);

	printf("Reverse = %d\n", reverse(num));
	printf(" last digit = %d.\n", lastdigit(num));
	printf(" sum = %d.", Sum(num));
	return 0;
}

int reverse(int num)
{
	int reverse = 0;
	for (; num != 0; num = num / 10)
	{
		reverse = reverse * 10 + lastdigit(num);
	}
	return reverse;
}

int lastdigit(int num)
{
	int last_digit;
	last_digit = num % 10;
	return last_digit;
}


int Sum(int num)
{
	int sum;
	for (sum = 0; num != 0; num = num / 10)
	{
		sum = sum + lastdigit(num);
	}
	return sum;
}

