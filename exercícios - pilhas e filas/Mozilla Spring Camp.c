#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//criar uma struct para a ação (node):
typedef struct node{
    char cmd[8];
    struct node *next;
}node;

//criar uma struct da stack:
typedef struct stack{
    node *top;
}stack;

//criar func para inicializar stack nula:
void create_stack(stack *stack){
    return stack->top = NULL;
}

//função push na stack:

void push(stack *stack, char cmd[]){
    node *new_node = (node*)malloc(sizeof(node));

    if(new_node == NULL){
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->cmd, cmd);
    new_node->next = stack->top;
    stack->top = new_node;
}

//func para dar pop:

void pop(stack *stack){
    if(stack->top == NULL){
        printf("EMPTY STACK!!\n");
        return;
    }

    node *aux = stack->top;
    stack->top = aux->next;
    free(aux);
}

//func para contar as ações BACK:

int count_back(stack *stack_back){
    int count = -1;

    node *aux = stack_back->top;

    while(aux != NULL){
        count++;
        aux = aux->next;
    }
    return count;
}

//func para contar as ações FORWARD

int count_forward(stack *stack_forward){
    int count = 0;

    node *aux = stack_forward->top;

    while(aux != NULL){
        count++;
        aux = aux->next;
    }
    return count;
}

int main(){
    stack stack_back;
    stack stack_forward;
    create_stack(&stack_back);
    create_stack(&stack_forward);

    char cmd[8];

    while(scanf("%s", cmd) != EOF){
        if(strcmp(cmd, "ENTER") == 0){
            while (stack_forward.top != NULL) {
                pop(&stack_forward);
            }
            push(&stack_back, cmd);
        }
        else if(strcmp(cmd, "BACK") == 0){
            if(stack_back.top != NULL){
                push(&stack_forward, stack_back.top->cmd);
                pop(&stack_back);
            }
        }
        else if(strcmp(cmd, "FORWARD") == 0){
            if(stack_forward.top != NULL){
                push(&stack_back, stack_forward.top->cmd);
                pop(&stack_forward);
            }
        }
    }

    int back = count_back(&stack_back);
    int forward = count_forward(&stack_forward);

    printf("BACK: %d\n", back);
    printf("FORWARD: %d\n", forward);

    return 0;
}