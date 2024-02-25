#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
}node;

node* add_end(node **head, int new_item)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = new_item;
    new_node->next = NULL;

    if (*head == NULL) 
    {
        *head = new_node;
    } 
    else 
    {
        node *current = *head;

        while (current->next != NULL) 
        {
            current = current->next;
        }

        current->next = new_node;
    }
}

node* reverse_list(node **head) // função para inverter lista
{
    node *prev = NULL; 
    node *current = *head;
    node *next = NULL;

    while(current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void print_list(node *head)
{
    while(head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
    }
    //printf("\n");
}

int main()
{
    node *head = NULL;
    int item;

    while(scanf("%d", &item) != EOF)
    {
        add_end(&head, item);
    }

    //printf("Lista Original:\n");
    //print_list(head);

    reverse_list(&head);

    //printf("Lista Invertida:\n");
    print_list(head);

    return 0;
}