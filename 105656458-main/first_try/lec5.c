#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int number;
    struct node* next;
}node;

int main()
{
    node* head = NULL;
    node* n = malloc(sizeof(node));
    if(n == NULL)
    {
        return 1;
    }
    n->number = 1;
    n->next = NULL;
    head = n;
    //---------------------------------
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(head);
        return 2;
    }
    n->number = 2;
    n->next = NULL;
    head->next = n;
    //--------------------------------
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(head->next);
        free(head);
        return 3;
    }
    n->number = 3;
    n->next = NULL;
    head->next->next = n;
    //--------------------------------
    for(node* tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    //freeeeeeeeeeeeee
    while(head != NULL)
    {
        node* tmp = head->next;
        free(head);
        head = tmp;
    }

}