#include<stdio.h>

char vowels(char);
int main()
{
	char i;
	printf("Enter the alphabet : ");
	scanf_s("%c", &i);

	if (vowels(i) == 1)
	{
		printf("This is a vowel.");
	}
	else
	{
		printf("This is a consonant.");
	}
	return 0;
}

char vowels(char j)
{
	char k = 0;
	if ((j == 'a') || (j == 'A') || (j == 'e') || (j == 'E') || (j == 'i') || (j == 'I') || (j == 'o') || (j == 'O') || (j == 'u') || (j == 'U'))
	{
		k = 1;
	}
	else
	{
		k = 0;
	}
	return k;
}

