#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string text1 = get_string("Player1: ");
    string text2 = get_string("Player2: ");
    int len1 = strlen(text1);
    int len2 = strlen(text2);
    int sum1 = 0;
    int sum2 = 0;
    int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    for(int i = 0; i < len1; i++)
    {
        if(isalpha(text1[i]) != 0)
        {
            sum1 += scores[toupper(text1[i]) - 65];
        }
    }
        for(int i = 0; i < len2; i++)
    {
        if(isalpha(text2[i]) != 0)
        {
            sum2 += scores[toupper(text2[i]) - 65];
        }
    }
    if(sum1 > sum2)
    {
        printf("Player 1 wins!\n");
    }
    else if(sum2 > sum1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}