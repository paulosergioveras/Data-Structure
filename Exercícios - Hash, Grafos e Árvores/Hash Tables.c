#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1000

typedef struct element {
    int key;
    struct element *next;
} element;

element *create_element(int key) {
    element *new_element = (element *)malloc(sizeof(element));
    if (new_element == NULL) {
        printf("ERROR!! \n");
        exit(EXIT_FAILURE);
    }

    new_element->key = key;
    new_element->next = NULL;
    return new_element;
}

void put(element **ht, int key, int ht_size) {
    int h = key % ht_size;

    element *new_element = create_element(key);

    if (ht[h] == NULL) ht[h] = new_element; 
    else{
        element *current = ht[h];
        while (current->next != NULL) current = current->next;
        current->next = new_element;
    }
}

void print_hash_table(element **ht, int ht_size) {
    for (int i = 0; i < ht_size; i++){
        printf("%d -> ", i);
        element *current = ht[i];
        while (current != NULL){
            printf("%d -> ", current->key);
            current = current->next;
        }
        printf("\\\n");
    }
    printf("\n");
}

int main(){
    int cases;
    scanf("%d", &cases);

    for (int i = 0; i < cases; i++){
        int qnt_end, qnt_key;
        scanf("%d %d", &qnt_end, &qnt_key);

        element **hash_table = (element **)malloc(sizeof(element) * qnt_end);
        for (int j = 0; j < qnt_end; j++){
            hash_table[j] = NULL;
        }

        for (int t = 0; t < qnt_key; t++){
            int keys;
            scanf("%d", &keys);
            put(hash_table, keys, qnt_end);
        }

        // print
        print_hash_table(hash_table, qnt_end);

        // libera memoria
        for (int k = 0; k < qnt_end; k++){
            element *current = hash_table[k];
            while (current != NULL){
                element *aux = current;
                current = current->next;
                free(aux);
            }
        }
        free(hash_table);
    }
    return 0;
}
