#include<stdio.h>
//Safiullah Shah 

int sides(int, int, int);
int main()
{
	int x, y, z;
	printf("Enter three numbers : ");
	scanf_s("%d%d%d", &x, &y, &z);

	if (sides(x, y, z) == 1)
	{
		printf("These are sides of a traingle.");
	}
	else
	{
		printf("These are not sides of a traingle.");
	}



	return 0;
}

int sides(int x, int y, int z)
{

	if ((x * x == y * y + z * z) || (y * y == x * x + z * z) || (z * z == x * x + y * y))
	{
		x, y, z = 1;
	}
	else
	{
		x, y, z = 0;
	}
	return x, y, z;
}
