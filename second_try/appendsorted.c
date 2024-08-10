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

    for(int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node* n = malloc(sizeof(node));
        if(n == NULL)
        {
            return 1;
        }

        n->number = number;
        n->next = NULL;

        //if list is empty
        if(list == NULL)
        {
            list = n;
        }
        //if number belongs to the begining of list
        else if(n->number < list->number)
        {
            n->next = list;
            list = n;
        }
        //if number belongs somewhere later in list
        else
        {
            for(node* ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if(ptr->next == NULL) // => belongs to the end
                {
                    ptr->next = n;
                    break;
                }
                //if in middle of list
                if(n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;

                }
            }
        }

    }
    //print numbers
    for(node* tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    //free memory
    node* tmp = list;
    while(tmp != NULL)
    {
        node* next = tmp->next;
        free(tmp);
        tmp = next;
    }
}
