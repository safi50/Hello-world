#include <stdio.h>
int main()
{
    float x, y;
    printf("Enter temperature in celcius: ");
    scanf_s("%f", &x);
  
    y = (x * 1.8) + 32;

    printf(" New temperature in Fahrenheit = %.1f\n", y);
    return 0;
}

