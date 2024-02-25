Pedro Mateus Veras Simões <pmvs@ic.ufal.br>
	
11:37 (há 1 minuto)
	
para mim
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack();

//Recebe um elemento e cria e retorna um novo node
// com o elemento passado
NODE* create_node(int element);

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack);

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack);

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element);

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char operation);

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size);

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));

}
STACK* Create_stack(){
    STACK *new_stack = (STACK*) malloc(sizeof(STACK));
    new_stack->head = NULL;
    return new_stack;
}

NODE* create_node(int element){
    NODE *new_top = (NODE*) malloc(sizeof(NODE));
    new_top->element = element;
    return new_top;
}

int IS_EMPTY(STACK* stack){
    return(stack == NULL);
}

int POP(STACK* stack){
    if(IS_EMPTY(stack)){
        printf("underflow");
        return -1;
    }
    int aux = stack->head->element;
    NODE *temp = stack->head;
    stack->head = temp->next;
    free(temp);
    return aux;
}

void PUSH(STACK* stack, int element){
    NODE *new_top = create_node(element);
    new_top->next = stack->head;
    stack->head = new_top;
}

void Calculadora(STACK* calculadora, int size){
    int i;
    char entr[1000];
    for(i = 0; i < size; i++){
        scanf("%s", &entr);
        if(entr[0] == '+' || entr[0] == '-' || entr[0] == '*' || entr[0] == '/'){
            result(calculadora, entr[0]);
        }else{
            PUSH(calculadora, atoi(entr));
        }
    }
}

void result(STACK* stack, char operation){
    int opr_one, opr_two;
    opr_one = POP(stack);
    opr_two = POP(stack);

    if(operation == '*'){
        PUSH(stack, opr_two*opr_one);
    }
    else if(operation == '+'){
        PUSH(stack, opr_two+opr_one);
    }
    else if(operation == '/'){
        PUSH(stack, opr_two/opr_one);
    }
    else if(operation == '-'){
        PUSH(stack, opr_two-opr_one);
    }
}