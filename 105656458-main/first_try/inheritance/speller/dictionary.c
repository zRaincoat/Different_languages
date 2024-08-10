// Implements a dictionary's functionality

#include "dictionary.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 26;
int wordscounter = 0;
// Hash table
node* table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int a = hash(word);
    node* cursor = table[a];
    while(cursor != NULL)
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        return false;
    }
    char curword[LENGTH + 1];
    while(fscanf(dict, "%s", curword) != EOF)
    {
        node* n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }
        int a = hash(curword);
        //if there is no elements in the 'bucket' yet
        if(table[a] == NULL)
        {
            table[a] = n;
            wordscounter++;
        }
        else
        {
            n->next = table[a];
            table[a] = n;
            wordscounter++;
        }
    }
    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordscounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node* cursor = table[i];
        node* tmp = cursor;
        while(cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
