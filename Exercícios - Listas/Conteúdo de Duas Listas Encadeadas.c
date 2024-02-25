#include <stdio.h>
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

int subset(node *A, node *B)
{
    node *aux_A = A;
    node *aux_B = B;

    while(aux_B != NULL)
    {
        int item_found = 0; // contador

        while(aux_A != NULL)
        {
            if(aux_A->item == aux_B->item)
            {
                item_found = 1;
                break;
            }

            aux_A = aux_A->next;  // passa para o proximo item
        }

        if(!item_found)
        {
            return 0; // nao encontrou numero, ou seja, B não é subconjunto de A
        }  

        aux_B = aux_B->next;
        aux_A = A;
        // basicamente aqui vou ver se o proximo numero da lista B está na lista A, então é necessário reiniciar aux_A para A dnv
        // pois é necessario verificar todos numeros de A
    }

    return 1;
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

void free_list(node *head)
{
    node *current = head;
    node *next;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    node *A = NULL; // lista encadeada A
    node *B = NULL; // lista encadeada B
    int size_A, size_B, items; // tamanho de A, tamanho de B, item a ser adicionado nas listas

    // inserir tamanho da lista 1:
    scanf("%d", &size_A);

    // adicionar items na lista A:
    for(int i = 0; i < size_A; i++)
    {
        scanf("%d", &items);
        add_end(&A, items);
    }

    // inserir tamanho da lista 2:
    scanf("%d", &size_B);

    // adicionar items na lista B:
    for(int i = 0; i < size_B; i++)
    {
        scanf("%d", &items);
        add_end(&B, items);
    }

    int issubset = 1;
    int notsubset = 0;

    if(subset(A, B))
    {
        printf("%d\n", issubset);
    }
    else
    {
        printf("%d\n", notsubset);
    }

    free_list(A);
    free_list(B);

    return 0;
}