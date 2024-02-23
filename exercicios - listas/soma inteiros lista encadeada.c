#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
}node;

node* create_list(){
    return NULL;
}

node* add_begin(node **head, int item)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = *head;
    return new_node;
}

void print_list(node *head){
    while(head != NULL){
        printf("%d ", head->item);
        head = head->next;
    }
   // printf("\n");
}

int size_list(node *head){
    node *current = head;
    int size = 0;

    while(current != NULL){
        size++;
        current = current->next;
    }

    return size;
}

node *remove_zero(node *head) {
    // Remove os zeros à esquerda desnecessários
    while (head != NULL && head->item == 0 && head->next != NULL) {
        node *temp = head;
        head = head->next;
        free(temp);
    }

    return head;
}

node *sum_lists(node *list1, node *list2) {
    if (list1 == NULL && list2 == NULL) {
        printf("Lista vazia!\n");
        return NULL;
    }

    node *result = NULL;
    node *current = NULL;
    int carry = 0;

    while (list1 != NULL || list2 != NULL) {
        //printf("list1 item %d\n", list1->item);
        //printf("list2 item %d\n", list1->item);
        //printf("carry %d\n", carry);

        int sum = carry + (list1 ? list1->item : 0) + (list2 ? list2->item : 0);
        carry = sum / 10;

        result = add_begin(&result, sum % 10);

        if (list1) list1 = list1->next;
        if (list2) list2 = list2->next;
    }

    if (carry > 0) {
        result = add_begin(&result, carry);
    }

    result = remove_zero(result);

    return result;
}

int main(){
    node *list1 = create_list();
    node *list2 = create_list();
    node *result = create_list();
    int item;

    while(scanf("%d", &item)){
        if(item == '+'){
            break;
        }
        list1 = add_begin(&list1, item);
    }

    while(scanf("%d", &item)){
        if(item == '='){
            break;
        }
        list2 = add_begin(&list2, item);
    }

    result = sum_lists(list1, list2);
    print_list(result);
    printf("\n");

    return 0;
}