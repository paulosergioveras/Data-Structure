#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 100

typedef struct pilha {
    ITEM vet[TAM];
    int topo;
} TPilha;

void create(TPilha *p) {
    p->topo = -1;
}

void destroy(TPilha *p) {
    p->topo = -1;
}

int isfull(TPilha *p) {
    return p->topo == TAM;
}

int isempty(TPilha *p) {
    return p->topo == -1;
}

void push(TPilha *p, ITEM x) {
    if( isfull(p) ) {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

ITEM pop(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    ITEM x = p->vet[p->topo];
    p->topo--;
    return x;
}

ITEM top(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    return p->vet[p->topo];
}

void inverte_palavras_frase(char frase[]) {
    TPilha stack;
    create(&stack);

    int i = 0;

    while (frase[i] != '\0') {

        //while principal para percorrer ate
        //o fim da string ser encontrado

        int j = i;

        while (frase[j] != ' ' && frase[j] != '\0') {

            //vai empilhandondo caracter por caracter na stack
            //e incrementando em j
            //se j for ' ' ou '\0' o while interno se encerra

            push(&stack, frase[j]);
            j++;
        }

        //esse while vai rodar enquanto a stack nao for vazia
        while (!isempty(&stack)) {
            //aqui basicamente vai pegar o top da stack
            //e coloca na posição frase[i]
            //depois i
            //proxima iteração vai acontecer a mesma coisa ate a stack estar vazia
            frase[i] = pop(&stack);
            i++;
        }

        //verifica se é um espaço
        //se for, significa que a palavra chegou no fim
        //e incrementa em i para a proxima palavra

        if (frase[j] == ' ') {
            i++;
        }
    }
}

int main(void) {
    char frase[TAM];

    gets(frase);
    printf("original = %s\n", frase);
    inverte_palavras_frase(frase);
    printf("invertida = %s\n", frase);
    
    return 0;
}
