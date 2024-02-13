#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
}node;

node* create_linked_list()
{
    return NULL;
}

int is_empty(node *head)
{
    return (head == NULL);
}

node* add_begin(node *head, int item)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = head;
    return new_node;
}

node* search(node *head, int item)
{
    while(head != NULL)
    {
        if(head->item = item)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void print_linked_list(node *head)
{
    while(head != NULL)
    {
        printf("%d\n", head->item);
        head = head->next;
    }
}

void sort_list(node *head)
{
    node *i, *j;
    int aux;

    for(i = head; i->next != NULL; i = i->next)
    {
        for(j = i->next; j != NULL; j = j->next)
        {
            if(i->item > j->item)
            {
                aux = i->item;
                i->item = j->item;
                j->item = aux;
            }
        }
    }
}

void new(node *head)
{
    node *aux;

    while(head->next != NULL)
    {
        if(head->item == head->next->item)
        {
            aux = head->next->next;
            free(head->next);
            head->next = aux;
        }
        else
        {
            head = head->next;
        }
    }
}

int main()
{
    node* list1 = create_linked_list();
    node* list2 = create_linked_list();
    int i, item;

    for(i = 0; i < 20; i++)
    {
        scanf("%d", &item);
        list1 = add_begin(list1, item);
    }

    for(i = 0; i < 20; i++)
    {
        scanf("%d", &item);
        if(search(list1, item) == item)
        {
            list2 = add_begin(list2, item);
        }
    }

    if(is_empty(list2))
    {
        printf("VAZIO");
    }
    else
    {
        sort_list(list2);
        new(list2);
        print_linked_list(list2);
    }
    return 0;
}