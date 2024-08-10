#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0;
    int words = 1;
    int sentences = 0;
    float L = 0;
    float S = 0;
    int len = strlen(text);
    for(int i = 0; i < len; i++)
    {
        if(isalpha(text[i]))
        {
            letters += 1;
        }
        else if(text[i] == ' ')
        {
            words += 1;
        }
        else if(text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences += 1;
        }
    }
    L = ((float)letters / words) * 100;
    S = ((float)sentences / words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}