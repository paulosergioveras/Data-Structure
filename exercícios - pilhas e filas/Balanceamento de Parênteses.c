#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    int top;
    char arr[255];
}stack;

void create_stack(stack *stack){
    stack->top = -1;
}

int is_empty(stack *stack){
    return stack->top == -1;
}

int is_full(stack *stack){
    return stack->top == 254;
}

void push(stack *stack, char exp){
    if(is_full(stack)){
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }

    stack->arr[++stack->top] = exp;
}

char pop(stack *stack){
    if(is_empty(stack)){
        printf("Empty Stack\n");
        exit(EXIT_FAILURE);
    }

    char exp = stack->arr[stack->top--];
    return exp;
}

int balancing_parents(char *exp, int n){
    stack stack;
    create_stack(&stack);

    for(int i = 0; i < n; i++){
        if(exp[i] == '(' || exp[i] == '['){
            push(&stack, exp[i]);
        }
        else if(exp[i] == ')' || exp[i] == ']'){
            if(is_empty(&stack)) return 0;

            char aux_top = pop(&stack);

            if((exp[i] == ')' && aux_top != '(') || (exp[i] == ']' && aux_top != '[')) return 0; 
        }
    }

    return is_empty(&stack) ? 1 : 0;
}

void scan_stack(){
    char exp[255];
    int n;
    scanf("%d", &n);
    getchar();

    for(int i = 0; i < n; i++){
        fgets(exp, 255, stdin); //ler a string
        int string_size = strlen(exp);
        //create_stack(stack);

       //remove as quebras de linha da string:
       if(exp[string_size - 1] == '\n'){
            exp[string_size - 1] = '\0';
            string_size--;
       } 

        printf("%s", balancing_parents(exp, string_size) ? "Yes\n" : "No\n");
    }    

}

/*void remove_blanked_spaces(char *str){
    int j = 0;

    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] != ' '){
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}*/

int main(){
    scan_stack();
    return 0;
}