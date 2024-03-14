#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element{
    int key;
    struct element *next;
}element;

typedef struct list{
    element *head;
}list;

typedef struct hash_table{
    int size;
    list *table;
}hash_table;

void put(hash_table *ht, int key){
    int h = key % ht->size;

    element *new_element = (element*)malloc(sizeof(element));
    new_element->key = key;
    new_element->next = NULL;

    if(ht->table[h].head == NULL) ht->table[h].head = new_element;
    else{
        element *current = ht->table[h].head;
        element *prev = NULL;

        //coloca os valores em ordem cresce dentro da tabela:
        while(current != NULL && current->key < key){
            prev = current;
            current = current->next;
        }

        // é o primeiro da lista
        //colocando o novo elemento na cabeça da lista
        if(prev == NULL){
            new_element->next = ht->table[h].head;
            ht->table[h].head = new_element;
        }
        else{
            prev->next = new_element;
            new_element->next = current;
        }
    }
}

void remove_element(hash_table *ht, int key){
    int h = key % ht->size;
    element *current = ht->table[h].head;
    element *prev = NULL;

    //percorre a lista enquanto o current nao for nulo e a chave atual nao for igual a chave de remoção
    while(current != NULL && current->key != key){
        prev = current;
        current = current->next;
    }

    if(current != NULL){
        // se o prev é nulo é pq é a cabeça da lista, ou seja, o elemento a ser removido é a cabeça
        // entao o ponteiro da cabeça tem que apontar para o proximo
        if(prev == NULL) ht->table[h].head = current->next;
        else prev->next = current->next; 
        // se nao for nulo é pq ta no meio ou no fim da lista
        // entao tem que atualizar para que o next anterior oponte para o proximo elemento
        // ignora o que vai ser removido
        free(current);
    }
}

void search(hash_table *ht, int key){
    int h = key % ht->size;
    element *current = ht->table[h].head;
    int count = 0;

    while(current){
        count++;
        if(current->key == key) break;
        current = current->next;
    }

    int count2 = 0;
    for(int i = 0; i < ht->size; i++){
        element *current2 = ht->table[i].head;
        while(current2){
            count2++;
            current2 = current2->next;
        }
    }
    
    if(current){
        printf("BUSCA POR %d\n", key);
        printf("numero de elementos da tabela hash: %d\n", count2);
        printf("elemento %d encontrado!\n", key);
        printf("numero de elementos acessados na tabela hash: %d\n", count);
    }else{
        printf("BUSCA POR %d\n", key);
        printf("numero de elementos da tabela hash: %d\n", count2);
        printf("elemento nao encontrado!\n");
        printf("numero de elementos acessados na tabela hash: %d\n", count);
    }
}

void print_hash_table(hash_table *ht){
    printf("imprimindo tabela hash:\n");
    for(int i = 0; i < ht->size; i++){
        printf("[%d]:", i);
        element *current = ht->table[i].head;
        while(current != NULL){
            printf("%d=>", current->key);
            current = current->next;
        }
        if(ht->table[i].head == NULL) printf("Lista vazia!");
        printf("\n");
    }
}

void free_hash_table(hash_table *ht){
    for(int i = 0; i < ht->size; i++){
        element *current = ht->table[i].head;
        element *aux;
        while(current != NULL){
            aux = current->next;
            free(current);
            current = aux;
        }
    }
    free(ht->table);
    free(ht);
}


int main(){
    char entrr;;
    int m, key;
    scanf("%d", &m);

    hash_table *ht = (hash_table*)malloc(sizeof(hash_table));
    ht->size = m;
    ht->table = (list*)malloc(sizeof(list) * m);

    for(int i = 0; i < m; i++){
        ht->table[i].head = NULL;
    }

    while(1){
        scanf(" %c", &entrr);
        switch(entrr){
            case 'a':
                scanf("%d", &key);
                put(ht, key);
                break;

            case 'r':
                scanf("%d", &key);
                remove_element(ht, key);
                break;

            case 'i':
                print_hash_table(ht);
                break;

            case 'p':
                scanf("%d", &key);
                search(ht, key);
                break;

            case 'f':
                return 0;
        }
    }
    free_hash_table(ht);
    return 0;
}