CODE:
#include<stdio.h>
int hourtosec(int, int, int);
int main()
{
    int hr, sec, min, minute;
    printf(" Enter the number of hours: ");
    scanf_s("%d", &hr);
    printf(" Enter the number of minutes: ");
    scanf_s("%d", &min);
    printf_s(" Enter the number of seconds: ");
    scanf_s("%d", &sec);

    minute = hourtosec(hr, min, sec);

    printf("\nThe time provided %d:%d:%d when converted to seconds is: %d ", hr, min, sec, minute);
}


int hourtosec(int hours, int minutes, int seconds)
{
    int result;
    result = (hours * 3600) + (minutes * 60) + (seconds);
    return result;
}



