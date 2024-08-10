#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node* next;
}node;

int main(int argc, char* argv[])
{
    node* list = NULL;

        //prepending elements

    for(int i = 1; i < argc; i++) // i starts with 1 because 0 is the name of the program :)
    {
        node* n = malloc(sizeof(node));

        if(n == NULL)
        {
            return 1;
        }

        int number = atoi(argv[i]);
        n->number = number;
        n->next = list;
        list = n;
    }
    //preinting
    node* ptr = list;
    while(ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    //free memory
    ptr = list;
    while(ptr != NULL)
    {
        node* next = ptr->next;
        free(ptr);
        ptr = next;
    }
}
