#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element{
    int key, item;
    struct element *next;
}element;

typedef struct hash_table{
    element *table[100000];
}hash_table;

hash_table *create_hash_table(int m){
    hash_table *new_hash_table = (hash_table*)malloc(sizeof(hash_table));
    for(int i = 0; i < m; i++){
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

//verifica se o elemento da dentro da tabela
int HAS(hash_table *ht, int key, int *vezes, int m){
    int status = 0;
    int h = key % m;
    element *head = ht->table[h];

    while(head != NULL){
        ++*vezes;
        if(key == head->item){
            status = 1;
            break;
        }
        head = head->next;
    }
    return status;
}

int ADD(hash_table *ht, int key, int *vezes, int m){
    int h = key % m;

    if(HAS(ht, key, &*vezes, m)) return 0;

    element *new_element = (element*) malloc(sizeof(element));
    new_element->key = key;
    new_element->item = key;
    new_element->next = NULL;

    if(ht->table[h] != NULL){
        element *aux = ht->table[h];
        ht->table[h] = new_element;
        new_element->next = aux;
    }
    else ht->table[h] = new_element;
    return 1;
}

void ADD_2(hash_table *ht, int key, int m){
    int h = key % m;
    element *new_element = (element*) malloc(sizeof(element));
    new_element->key = key;
    new_element->item = key;
    new_element->next = NULL;

    if(ht->table[h] != NULL){
        element *aux = ht->table[h];
        ht->table[h] = new_element;
        new_element->next = aux;
    }
    else    ht->table[h] = new_element;
}

element* remove_element(element *head, int item, int *vezes){
    element *prev = NULL;
    element *current = head;

    while(current != NULL && current->item != item){
        prev = current;
        current = current->next;
    }

    if(current == NULL) return head;

    if(prev == NULL) head = current->next;
    else prev->next = current->next;
    free(current);
    return head;
}

int DEL(hash_table *ht, int key, int *vezes, int m){
    int h = key % m;
    if(!HAS(ht, key, &*vezes, m)) return 0;
    ht->table[h] = remove_element(ht->table[h], key, &*vezes);
    return 1;
}

int biggest(hash_table *ht, int m){
    int count = 0, big = 0;

    for(int i = 0; i < m; i++){
        element *head = ht->table[i];
        while(head != NULL){
            count++;
            head = head->next;
        }
        if(count > big) big = count;
        count = 0;
    }
    return big;
}

int all(hash_table *ht, int m){
    int i, count = 0;

    for(i = 0; i < m; i++){
        element *head = ht->table[i];
        while(head != NULL){
            count++;
            head = head->next;
        }
    }
    return count;
}

hash_table* rehashing(hash_table *ht, int m){
    hash_table *new_ht = create_hash_table(m);

    for(int i = 0; i < ((m+1)/2); i++){
        element *head = ht->table[i];
        while(head != NULL){
            ADD_2(new_ht, head->item, m);
            head = head->next;
        }
    }
    return new_ht;
}

int main(){
    char op[50], aux[50];
    int num, count = 0;
    int times = 0, m = 7, n;
    float a;  //Fator de carga

    hash_table *ht = create_hash_table(m);

    while (scanf("%s", op) == 1) {
        if (strcasecmp(op, "PRT") != 0){
            scanf("%s", aux);
            num = atoi(aux);
        }
        printf("%d ", count);

        if (strcasecmp(op, "ADD") == 0){
            printf("%d ", ADD(ht, num, &times, m));
            printf("%d\n", times);
            n = all(ht, m);
            a = (float)n / m;

            if (a >= 0.75) {
                m = 2 * m - 1;
                ht = rehashing(ht, m);
            }
        }

        if (strcasecmp(op, "DEL") == 0) {
            printf("%d ", DEL(ht, num, &times, m));
            printf("%d\n", times);
        }

        if (strcasecmp(op, "HAS") == 0) {
            printf("%d ", HAS(ht, num, &times, m));
            printf("%d\n", times);
        }

        if (strcasecmp(op, "PRT") == 0) {
            printf("%d ", m);
            printf("%d ", all(ht, m));
            printf("%d\n", biggest(ht, m));
        }

        count++;
        times = 0;

        for (int l = 0; l < 50; l++) {
            op[l] = '\0';
            aux[l] = '\0';
        }
    }
    return 0;
}