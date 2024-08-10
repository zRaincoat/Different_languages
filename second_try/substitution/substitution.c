#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool check(void);
int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    if(strlen(argv[1]) != 26)
    {
        printf("Usage: ./substitution key");
        return 2;
    }
    if(!check)
    {
        printf("Usage: ./substitution key");
        return 3;
    }
    printf("kaban");

}


bool check(void)
{
    int sum = 0;
    int real_sum = 0;
    for(int i = 0; i < 26; i++)
    {
        sum += touppeer(argv[1][i]) - 65;
        real_sum += i;
    }
    if(real_sum == sum)
    {
        return true;
    }
    return false;
}