#include <cs50.h>
#include <stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

int count_letters(string text, int length);
int count_words(string text, int length);
int count_sentences(string text, int length);

int main(void)
{
    string text = get_string("Text:");
    int n = strlen(text);
    int letters = count_letters(text, n);
    int sentences = count_sentences(text, n);
    int words = count_words(text, n);
    float L = (float)letters / (float)words * 100;
    float S = (float)sentences / (float)words * 100;
    float x = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(x);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index > 16)
    printf("Grade 16+\n");
    else
    {
        printf("Grade %i\n", index);
    }
}


int count_letters(string text, int length)
{
    int letters = 0;
    for(int i = 0; i < length; i++)
    {
        if(isalpha(text[i]))
        {
            letters++;
        }
    }
return letters;
}

int count_words(string text, int length)
{
    int words = 1;
    for(int i = 0; i < length;i++)
    {
        if(text[i] == 32)
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text, int length)
{
    int sentences = 0;
    for(int i = 0;i < length;i++)
    {
        if(text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}