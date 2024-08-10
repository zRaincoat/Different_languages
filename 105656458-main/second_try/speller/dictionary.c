// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

int dicksize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lowercase_word[LENGTH + 1];
    for (int i = 0; word[i] != '\0'; i++)
    {
        lowercase_word[i] = tolower(word[i]); // Convert word to lowercase
    }
    lowercase_word[strlen(word)] = '\0'; // Add null terminator

    node *ptr = table[hash(lowercase_word)];
    while (ptr != NULL)
    {
        if (strcmp(lowercase_word, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int letter1 = toupper(word[0]) - 'A';
    int letter2 = toupper(word[1]) - 'A';
    return letter1 * letter2;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while(fscanf(file, "%s", buffer) != EOF)
    {
        dicksize++;
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        //copy word to node
        strcpy(n->word, buffer); // NIGGA
        //hash new word
        unsigned int hash_val = hash(buffer);
        //preapend new node
        n->next = table[hash_val];
        table[hash_val] = n;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dicksize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node* tmp = NULL;
    node* tmp_next = NULL;

    for (int i = 0; i < 26*26; i++)
    {
        tmp = table[i];
        while(tmp != NULL)
        {
            tmp_next = tmp->next;
            free(tmp);
            tmp = tmp_next;
        }
        table[i] = NULL;
    }
    return true;
}
