#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    if(argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    if(strlen(key) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    for(int i = 0; i < 26;i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Usage: ./substitution KEY\n");
            return 1;
        }
    }
    for(int j = 0; j < 26;j++)
    {
        for(int i = 0; i < 25 - j;i++)
        {
            if(key[j] == key[j+i+1])
            {
                printf("Key must not contain repeated charecters.\n");
                return 1;
            }
        }
    }
    string text = get_string("Plaintext:");
    int n = strlen(text);
    for(int i = 0;i < 26;i++)
    {
        if(islower(key[i]))
        {
            key[i] = key[i] - 32; //convert the key to upper letters
        }
    }
    printf("ciphertext: ");
    for(int i = 0;i < n;i++)
    {
        if(isupper(text[i]))
        {
            int letter = text[i] - 65;
            printf("%c", key[letter]);
        }
        else if(islower(text[i]))
        {
            int letter = text[i] - 97;
            printf("%c", key[letter] + 32);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}