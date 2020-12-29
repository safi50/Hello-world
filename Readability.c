#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int get_index(string s);
int main(void)
{
    // prompting user for text
    string text = get_string("Text: ");
    int index = get_index(text);
    
    // declaring printouts
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
    return 0;
}
// declaring string s
int get_index(string s)
{
    // declaring variables
    int letters = 0, sentence = 0, words = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        char ch = s[i];
        if (isalpha(ch))
        {
            letters ++;
        }
        if (isspace(ch))
        {
            words ++;
        }
        if (ch == '!' || ch == '?' || ch == '.')
        {
            sentence ++;
        }
    }
    words++;
    // implementing formula
    float L = (letters * 100.0f) / words;
    float S = (sentence * 100.0f) / words;
    // rounding answer
    return round(0.0588 * L - 0.296 * S - 15.8);

}
