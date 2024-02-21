#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct pilha_dupla {
    ITEM vet[TAM];
    int topo1, topo2;
} TPilhaDupla;

void create(TPilhaDupla *pd) {
	//Insira o código aqui
    pd->topo1 = -1;
    pd->topo2 = TAM;
}

void destroy(TPilhaDupla *pd) {
	//Insira o código aqui

}

int isfull(TPilhaDupla *pd) {
	//Insira o código aqui
    //para a pilha estar cheia, o topo1 tem que estar na posição seguinte
    //ou seja, topo1 + 1
    //e isso tem que ser ter o mesmo valor de topo2
    pd->topo1 + 1 == pd->topo2;
}

int isempty(TPilhaDupla *pd, int topo) {
	//Insira o código aqui
    //topo seria a checagem de qual stack, ou qual topo (topo1 ou topo2)
    //para qual será verificado se é vazio ou nao
    if(topo == 1){
        return pd->topo1 == -1;
    }
    else if(topo == 2){
        return pd->topo2 == TAM;
    }
    else{
        return -1;
    }
    
}

void push(TPilhaDupla *pd, ITEM x, int topo) {
	//Insira o código aqui
    
    //primeira verificação é se pd está cheio:

    if(isfull(pd)){
        printf("Full stack\n");
        return;
    }

    //segunda verificação é de qual topo estamos usando:

    if(topo == 1){
        //antes da inserção de um novo item
        //será reposicionado para a posição sucessora
        //crescerá em direção ao fim do vetor. 
        //ou seja, vai incrementar antes de adicionar
        pd->vet[++pd->topo1] = x;
    }
    else if(topo == 2){
        //antes da inserção de um novo item
        //será reposicionado para a posição antecessora
        //crescerá em direção ao início do vetor. 
        //ou seja, vai decrementar antes de adicionar
        pd->vet[--pd->topo2] = x;
    }
    else{
        return;
    }
}

ITEM pop(TPilhaDupla *pd, int topo) {
	//Insira o código aqui

    //primeira verificação é a pilha nao está vazia:

    ITEM item;

    if(isempty(pd, topo)){
        //printf("Empty stack.\n");
        return (ITEM)0;
    }

    //segunda verificação é ver qual topo estamos usando:

    if(topo == 1){
        item = pd->vet[pd->topo1--];
        //primeiro armazena o valor do topo da pilha e depois decrementa a pilha;
    }
    else if(topo == 2){
        item = pd->vet[pd->topo2++];
        //primeiro armazena o valor do topo da pilha e depois incrementa a pilha;
    }
    else{
        return (ITEM)0;
    }
    return item;
}

ITEM top(TPilhaDupla *pd, int topo) {
	//Insira o código aqui

    //primeira verificação é se a pd não é vazia:

    if(isempty(pd, topo)){
        return (ITEM)0;
    }

    //segunda verificação é de qual topo(pilha) estamos utilizando
    //depois retornar o top de cada pilha

    if(topo == 1){
        return pd->vet[pd->topo1];
    }
    else if(topo == 2){
        return pd->vet[pd->topo2];
    }
    else{
        return (ITEM)0;
    }
}

void preenche(TPilhaDupla *pd) {
    ITEM x;
    int topo, qtd, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &topo);
        push(pd, x, topo);
    }
}

void exibe(TPilhaDupla *pd) {
    int topo;

    while( scanf("%d", &topo) != EOF){
        printf("TOPO %d = %c\n", topo, pop(pd, topo));
    }

}

int main(void) {
    TPilhaDupla pd;

    create(&pd);
    preenche(&pd);
    exibe(&pd);
    destroy(&pd);

    return 0;
}