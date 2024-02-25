#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definindo struct de lista encadeada:

typedef struct node{
    int item;
    struct node *next;
}node;

//definindo struct de um nó na pilha:

typedef struct stack_node{
    node *start_list;
    struct stack_node *next;
}stack_node;

//definindo struct da pilha:

typedef struct Stack{
    stack_node *top;
}Stack;

//função para criar lista vazia:

node *create_linked_list(){
    return NULL;
}

//função para criar stack vazia

Stack *create_stack(){
    Stack *stack = (Stack*)malloc(sizeof(Stack));

    if(stack == NULL) exit(EXIT_FAILURE);

    stack->top = NULL;
    return stack;
}

//função para adicionar no final da lista:

node* add_end_list(node *head, int new_item){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = new_item;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    } 
    else {
        node *current = head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_node;
        return head;
    }
}

//função para adicionar no inicio do nó da stack:

stack_node *add_begin_stack(stack_node *top){
    stack_node *new_node = (stack_node*)malloc(sizeof(stack_node));

    if(new_node == NULL) exit(EXIT_FAILURE);

    new_node->start_list = create_linked_list();
    new_node->next = top;
    return new_node;
}

//função para remover quebra de linha de uma string:

void remove_line_break(char *str){
    int line_break = strcspn(str, "\n");
    str[line_break] = '\0';
}

void print_list(node *head) {
    if (head == NULL) {
        printf("\tEMPTY STACK\n");
        return;
    }

    //printf("\t");

    while (head != NULL) {
        printf("%d", head->item);
        if (head->next != NULL) {
            printf(" ");
        }
        head = head->next;
    }

    printf("\n");
}

void scan_stack(Stack *stack){
    char cmd[5];
    char aux;
    int item;

    while(fgets(cmd, 5, stdin) != NULL){
        remove_line_break(cmd);

        if(strcmp(cmd, "PUSH") == 0){
            //se o comando PUSH for dado
            //inicia um nó no inicio da stack

            stack->top = add_begin_stack(stack->top);

            //vai percorrer o while e colocar os items no final da lista
            while(scanf("%d%c", &item, &aux) == 2){
                stack->top->start_list = add_end_list(stack->top->start_list, item);

                if(aux == '\n') break; //se o ultimo caracter for uma quebra de linha, entao encerra
            }
        }
        else if(strcmp(cmd, "POP") == 0){
            if(stack->top == NULL) printf("EMPTY STACK\n");
            else{
                print_list(stack->top->start_list);

                //liberação de memoria:

                stack_node *aux_m = stack->top;
                stack->top = stack->top->next;
                free(aux_m);
            }

        }
    }
}

void free_stack(Stack *stack){
    while(stack->top != NULL){
        stack_node *aux = stack->top;
        stack->top = stack->top->next;

        while(aux->start_list != NULL){
            node *aux_node = aux->start_list;
            aux->start_list = aux->start_list->next;
            free(aux_node);
        }
        free(aux);
    }
    free(stack);
}

int main(){
    Stack *stack = create_stack();
    scan_stack(stack);
    free_stack(stack);
    return 0;
}