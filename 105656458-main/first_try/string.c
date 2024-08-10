#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26 // number of letters in the alphabet

typedef struct node {
    char* word;
    struct node* next;
} node;

// function to create a new node with a word
node* create_node(char* word) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->word = (char*) malloc(strlen(word) + 1);
    strcpy(new_node->word, word);
    new_node->next = NULL;
    return new_node;
}

// function to add a node to the hash table
void add_node(node** table, char* word) {
    int index = word[0] - 'A'; // get the first letter of the word and convert it to an index
    node* new_node = create_node(word);
    if (table[index] == NULL) {
        table[index] = new_node;
    } else {
        node* current = table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// function to print the hash table
void print_table(node** table) {
    printf("Hash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("[%c]: ", i + 'A');
        if (table[i] == NULL) {
            printf("EMPTY");
        } else {
            node* current = table[i];
            while (current != NULL) {
                printf("%s -> ", current->word);
                current = current->next;
            }
            printf("NULL");
        }
        printf("\n");
    }
}

// function to free the memory used by the hash table
void free_table(node** table) {
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != NULL) {
            node* current = table[i];
            while (current != NULL) {
                node* temp = current;
                current = current->next;
                free(temp->word);
                free(temp);
            }
        }
    }
    free(table);
}

int main() {
    // initialize the hash table with NULL values
    node** table = (node**) calloc(SIZE, sizeof(node*));

    // fill the hash table with 100 random English words
    char words[30][20] = {"Abundant", "Mystery", "Whisper", "Graceful", "Luminous", "Gentle", "Radiant", "Serenity", "Surreal", "Gleaming", "Echo", "Wanderlust", "Nostalgia", "Intricate", "Lively", "Ethereal", "Harmony", "Majestic", "Tranquil", "Jovial", "Enchanting", "Euphoria", "Luminous", "Mellifluous", "Serendipity", "Simplicity", "Spectral", "Sultry", "Mellifluous", "Effervescent"};

for (int i = 0; i < 100; i++) {
    add_node(table, words[i]);
} with DeepL
Translate your own words with one click—right here!

 with DeepL
Translate your own words with one click—right here!

// print the hash table
print_table(table);

// free the memory used by the hash table
free_table(table);

return 0;
}
