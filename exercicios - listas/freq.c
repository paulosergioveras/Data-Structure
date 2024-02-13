#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char char_value;
    int frequency;
    struct Node* next;
} Node;

Node* create_linked_list(char* text) {
    int char_frequency[256] = {0};  // Inicializa um array para contar a frequência de cada caractere
    
    // Conta a frequência de cada caractere no texto
    for (int i = 0; text[i] != '\0'; i++) {
        char_frequency[(unsigned char)text[i]]++;
    }
    
    Node* head = NULL;
    Node* tail = NULL;
    
    // Cria a lista encadeada
    for (int i = 0; i < 256; i++) {
        if (char_frequency[i] > 0) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->char_value = (char)i;
            new_node->frequency = char_frequency[i];
            new_node->next = NULL;
            
            if (head == NULL) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }
    
    return head;
}

void print_linked_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%c %d\n", current->char_value, current->frequency);
        current = current->next;
    }
}

void free_linked_list(Node* head) {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    printf("Digite um texto: ");
    
    char text[1000];
    fgets(text, sizeof(text), stdin);
    
    Node* linked_list_head = create_linked_list(text);
    print_linked_list(linked_list_head);
    
    // Liberar a memória alocada para a lista encadeada
    free_linked_list(linked_list_head);
    
    return 0;
}
