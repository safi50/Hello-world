#include <stdio.h>

int main()
{
	int percentage;
	char grade;
	scanf_s("%d", &percentage);
	if (percentage > 100 || percentage < 0)
	{
		printf("Please enter a valid percentage");
		return 1;
	}
	else if (percentage >= 90) {
		grade = 'A';
	}
	else if (percentage >= 80) {
		grade = 'B';
	}
	else if (percentage >= 70) {
		grade = 'C';
	}
	else if (percentage >= 60) {
		grade = 'D';
	}
	else {
		grade = 'F';
	}
	printf("Your Grade = %c", grade);
	return 0;
}

