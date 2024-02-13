#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
}node;

node* create_linked_list(){
    return NULL;
}

node* add_begin(node *head, int item){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = head;
    return new_node;
}

void print_list(node *head){
    while(head != NULL){
        printf("%d ", head->item);
        head = head->next;
    }
}

void swap(node *a, node *b){
    int aux = a->item;
    a->item = b->item;
    b->item = aux;
}

void sort_list(node *head){
    int aux;
    node *pointer_one;
    node *pointer_two = NULL;

    while(1){
        aux = 0;
        pointer_one = head;

        if(head == NULL) return;

        while(pointer_one->next != pointer_two){
            if(pointer_one->item > pointer_one->next->item){
                swap(pointer_one, pointer_one->next);
                aux = 1;
            }
            pointer_one = pointer_one->next;
        }

        if(!aux) break;

        pointer_two = pointer_one;
    }
}

int main(){
    node *list = create_linked_list();
    int num;

    while(scanf("%d", &num) != EOF){
        list = add_begin(list, num);
    }

    sort_list(list);
    print_list(list);

    return 0;
}