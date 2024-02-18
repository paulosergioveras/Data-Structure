#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct deque {
    ITEM vet[TAM];
    int front, rear;
} TDeque;

void create(TDeque *d) {
	//Insira o código aqui
    d->front = d->rear = -1;
    // aqui é como se o inicio e o fim fosse o mesmo
    // o principio e o fim HEHEHEHE
}

void destroy(TDeque *d) {
	//Insira o código aqui
    d->front = d->rear = -1;
}

int isfull(TDeque *d) {
	//Insira o código aqui

    // deque está quando o prox index do rear é igual ao front
    return ((d->front == 0 && d->rear == TAM - 1) || (d->front == d->rear + 1));
}

int isempty(TDeque *d) {
	//Insira o código aqui
    return (d->front == -1);
}

void store(TDeque *d, int extremidade, ITEM x) {
	//Insira o código aqui

    // verificar se o deque está cheio:
    if(isfull(d)){
        exit(EXIT_FAILURE);
    }

    // se d->front == -1, inicializa front e rear
    // extremidade == 1 -> inseri no front
    // extremidade == 2 -> inseri no rear

    if(d->front ==  -1){
        d->front = d->rear = 0;
    }
    else if(extremidade == 1){
        //d->front - 1 decrementa circularmente
        // + TAm faz com que o resultado seja positivo
        // % TAM garante que o resultado esteja dentro do array
        d->front = (d->front - 1 + TAM) % TAM;
    }
    else{
        // d->rear + 1 incremente circularmente
        // % TAM garante que o resultado esteja dentro do array
        d->rear = (d->rear + 1) % TAM;
    }
    d->vet[(extremidade == 1 ? d->front : d->rear)] = x;
    // se extremidade == 1, d->vet[d->front]
    // se for diferente de 1, d->vet[d->rear] 
}

ITEM retrieve(TDeque *d, int extremidade) {
	//Insira o código aqui
    if(isfull(d)){
        exit(EXIT_FAILURE);
    }

    ITEM x = d->vet[(extremidade == 1 ? d->front : d->rear)];

    if(d->front == d->rear){
        d->front = d->rear = -1; // reinicia a deque
    }
    else if(extremidade == 1){
        d->front = (d->front + 1) % TAM;
    }
    else{
        d->rear = (d->rear - 1 + TAM) % TAM;
    }
    return x;
}

void preenche(TDeque *d) {
    ITEM x;
    int qtd, extremidade, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &extremidade);
        store(d, extremidade, x);
    }
}

void exibe(TDeque *d) {
    int extremidade;

    while( scanf("%d", &extremidade) != EOF ) {
		if( extremidade==1 )
        	printf("INICIO = %c\n", retrieve(d, extremidade));
		else
			printf("FIM = %c\n", retrieve(d, extremidade));
	}
}

int main(void) {
    TDeque d;

    create(&d);
    preenche(&d);
    exibe(&d);
    destroy(&d);

    return 0;
}
