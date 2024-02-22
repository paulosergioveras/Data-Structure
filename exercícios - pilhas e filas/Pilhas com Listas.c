#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int item;
    struct node *next;
}node;

typedef struct stack{
    node *top;
}Stack;

void create_stack(Stack *stack){
    stack->top = NULL;
}

void push(Stack *stack, int item){
    node *new_node = (node*)malloc(sizeof(node));

    if(new_node == NULL){
        exit(EXIT_FAILURE);
    }

    new_node->item = item;
    new_node->next = stack->top;
    stack->top = new_node;
}

void print_stack(){
    
}

void pop(Stack *stack){
    if(stack->top == NULL){
        printf("EMPTY STACK\n");
        return;
    }

    while(stack->top != NULL){
         node *aux = stack->top;
        stack->top = stack->top->next;
        printf("%d\n", aux->item);
        free(aux);
    }
   
}

int main(){
    Stack stack;
    create_stack(&stack);

    char cmd[20];
    int item;

    while(scanf("%s", cmd) != EOF){
        if(strcmp(cmd, "PUSH") == 0){
            while(scanf("%d", &item) == 1){
                push(&stack, item);
            }
        }
        else if(strcmp(cmd, "POP") == 0){
            pop(&stack);
        }
        else{
            exit(EXIT_FAILURE);
        }
    }

    while(stack.top != NULL){
        pop(&stack);
    }

    return 0;
}