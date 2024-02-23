#include <stdio.h>
#include <stdlib.h>

#define size 256

typedef struct node{
    char letter;
    int freq;
    struct node *next;
}node;

node* create_node(char letter){
    node *new_node = (node*)malloc(sizeof(node));

    if(new_node == NULL){
        fprintf(stderr, "erro\n");
        exit(EXIT_FAILURE);
    }

    new_node->letter = letter;
    new_node->freq = 1;
    new_node->next = NULL;
    return new_node;
}

node* start_linked_list(){
    node *temp = create_node('\0'); // cria uma lista com caracter nulo
    temp->next = NULL;
    return temp;
}

// coloca na ordem decrescente:

void aux_add_node(node *current, char letter){
    node *aux_node = create_node(letter);
    aux_node->next = current->next;
    current->next = aux_node;
}

// adiciona o nó de forma DECRESCENTE de acordo com a tabela ASCII:

// adiciona o nó de forma DECRESCENTE de acordo com a tabela ASCII:
void add_node(node *head, char letter) {

    // nao adiciona quebra de linha na lista
    if (letter == '\n') {
        return;
    }

    node *current = head;

    // percorre a lista e encontra a melhor posição: (melhor posição sera a decrescente)
    while (current->next != NULL && current->next->letter > letter) {
        current = current->next;
    }

    // verifica se ja existe a letra na lista
    // ee tiver, incrementa na frequência
    if (current->next != NULL && current->next->letter == letter) {
        current->next->freq++;
    }
    else{
        // se não, chama a função auxiliar para adicionar o novo nó
        aux_add_node(current, letter);
    }
}


void print_linked_list(node *head){
    node *current = head->next;
    while(current != NULL){
        printf("%c %d\n", current->letter, current->freq);
        current = current->next;
    }
}

void free_list(node *head){
    node *current = head;
    node *next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

int main(){
    char txt[size];
    fgets(txt, size, stdin);
    node *list = start_linked_list();

    for(int i = 0; txt[i] != '\0'; i++){
        add_node(list, txt[i]);
    }

    print_linked_list(list);
    free_list(list);

    return 0;
}