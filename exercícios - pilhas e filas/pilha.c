#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int item;
    struct node *next;
}node;

typedef struct stack{
    node *top;
}STACK;

void start_stack(STACK *stack){
    stack->top = NULL;
}

int is_empty(STACK *stack){
    return stack->top == NULL;
}

// func para adicionar elemento na pilha:

void push(STACK *stack, int item){
    node *new_node = (node*)malloc(sizeof(node));

    if(new_node == NULL){
        exit(EXIT_FAILURE);
    }

    new_node->item = item;
    new_node->next = stack->top;
    stack->top = new_node;

}

// func para retirar elemento da pilha:

void pop(STACK *stack){
    if(is_empty(stack)){
        exit(EXIT_FAILURE);
    }

    node *aux = stack->top;
    stack->top = stack->top->next;
    free(aux);
}

void print_stack(STACK *stack){
    node *current = stack->top;

    while(current != NULL){
        printf("%d", current->item);
        current = current->next;
        if(current != NULL){
            printf(" ");
        }
    }
    printf("\n");
}

int main(){
    STACK stack;
    start_stack(&stack);

    int item;
    char cmd[100];

    while(1){
        scanf("%s", cmd);

        if(strcmp(cmd, "Empilhar") == 0){
            scanf("%d", &item);
            push(&stack, item);
        }
        else if(strcmp(cmd, "Desempilhar") == 0){
            pop(&stack);
        }
        else if(strcmp(cmd, "Imprimir") == 0){
            print_stack(&stack);
        }
        else if(strcmp(cmd, "Finalizar") == 0){
            break;
        }
        else{
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}