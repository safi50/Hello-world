CODE:
#include <stdio.h>
#include <stdlib.h>

//Syed Safiullah Shah  
int sum(int num1, int num2)
{
	int add;
	 add = num1 + num2;
	return add;
}
int minus(int num1, int num2)
{
	int sub;
	 sub = num1 - num2;
	return sub;
}
int multiply(int num1, int num2)
{
	int mult;
	 mult = num1 * num2;
	return mult;
}
int divide(int num1, int num2)
{
	int div;
	div = num1 / num2;
	return div;
}

int main()
{
	int num1, num2;
	printf("\n Enter the num1 and num2 : ");
	scanf_s("%d %d", &num1,&num2);
	
	// Completing code 
	char operator;
	printf("Enter an operator (+, -, *, /): ");
	scanf_s("%c", &operator);

	switch (operator)
	{
	case '+' :
		int j;
		j = sum(num1, num2);
		printf("The sum is %d\n", j);
		break;
	case '-':
		int k;
		k = minus(num1, num2);
		printf("The minus is %d\n", k );
		break;
	case '*':
		int l;
		l = multiply(num1, num2);
		printf("The product is %d\n",l);
		break;
	case '/':
		int m; 
		m = divide(num1, num2);
		printf("The division is %d\n", m);
		
		break;

	default: 
		printf("Error! operator is not correct\n");
		break;
	}
	
	return 0;
}

