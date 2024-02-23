#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int item;
    struct node *next;
} node;

node* create_linked_list(){
    return NULL;
}

node* add_end(node *head, int new_item)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = new_item;
    new_node->next = NULL;

    if (head == NULL){
        return new_node;
    }
    
    node *current = head;

    while(current->next != NULL){
        current = current->next;
    }
    current->next = new_node;

    return head;  
}

void free_list(node *head)
{
    node *current = head;
    node *next;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void greatest_sequence(node *head){
    node *current = head;

    int max_count = 0, count = 0, i = 0;
    int max_begin = 0, current_begin = 0;
    

    while (current != NULL) {

        if (current->item == 0) {
            
            if (count == 0) {
                current_begin = i;
            }
            count++;
        }
        else{

            if (count > max_count) {
                max_count = count;
                max_begin = current_begin;
            }
            count = 0;
        }
        
        current = current->next;
        i++;
    }
    if (count > max_count) {
        max_count = count;
        max_begin = current_begin;
    }

    printf("%d %d\n", max_begin, max_begin + max_count - 1);
}

int main(){
    char *sequence_var = (char*) malloc(sizeof(char) * 100);

    while (fgets(sequence_var, 100, stdin)) { // read the sequence_var
        sequence_var[strcspn(sequence_var, "\n")] = 0; // remove '\n' and put '\0' (null)

        if (strcmp(sequence_var, "0") == 0 && strlen(sequence_var) == 1) { // compare two strings AND see if the lenght of sequence_var is 1
            break;
        }

        node *list = create_linked_list();
        
        for (int i = 0; sequence_var[i] != 0; i++) {
            if (sequence_var[i] == '0' || sequence_var[i] == '1') {
               list = add_end(list, sequence_var[i] - '0');
            }
        }

        greatest_sequence(list);
        free_list(list);
    }
    
    free(sequence_var);
    return 0;
}