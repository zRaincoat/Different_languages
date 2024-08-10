// Implements a list of numbers as a binary search tree
//   2
//  | |
//  1 3

#include <stdio.h>
#include <stdlib.h>

// Represents a node
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void free_tree(node *root);
void print_tree(node *root);

int main(void)
{
    //create a pointer to the root
    node* tree = NULL;
    //add first element (2)
    node* n = malloc(sizeof(node));
    if(n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;
    //adding 1
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(tree);
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;
    //adding 2
    n = malloc(sizeof(node));
    if(n == NULL)
    {
        free(tree);
        return 1;
    }
    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    print_tree(tree);
    free_tree(tree);
}


void print_tree(node* root)
{
    if(root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}

void free_tree(node* root)
{
    if(root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
