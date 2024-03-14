#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAMES_SIZE 17 
#define MAX_SIZE 100

typedef struct adj_list {
    int item;
    struct adj_list* next;
} adj_list;

typedef struct names {
    char name[MAX_NAMES_SIZE];
    int item;
    struct names* next;
} names;

typedef struct graph {
    int current_size;
    int* visited;
    adj_list** list;
} graph;

adj_list* create_adj_list(adj_list* head, int item) {
    adj_list* new_adj_list = (adj_list*)malloc(sizeof(adj_list));
    new_adj_list->item = item;
    new_adj_list->next = head;
    return new_adj_list;
}

graph* create_graph() {
    graph* new_graph = (graph*)malloc(sizeof(graph));
    new_graph->current_size = 0; // Inicializado para 0, será atualizado conforme necessário
    new_graph->list = (adj_list**)malloc(MAX_SIZE * sizeof(adj_list*)); // Correção da alocação
    new_graph->visited = (int*)malloc(MAX_SIZE * sizeof(int));
    for (int i = 0; i < MAX_SIZE; i++) {
        new_graph->visited[i] = 0; // Inicializado para 0
        new_graph->list[i] = NULL;
    }
    return new_graph;
}

adj_list* remove_item(adj_list* head, int item) {
    if (head == NULL) return head;

    adj_list* current = head;
    adj_list* prev = NULL;

    while (current != NULL && current->item != item) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return head;
    if (prev == NULL) head = head->next;
    else prev->next = current->next;
    free(current);
    return head;
}

names* add_names(names* head, char name[], int item) {
    names* new_node_name = (names*)malloc(sizeof(names));
    new_node_name->item = item;
    new_node_name->next = NULL;
    strcpy(new_node_name->name, name);

    if (head == NULL || strcmp(name, head->name) <= 0) {
        new_node_name->next = head;
        return new_node_name;
    }

    names* current = head;
    names* prev = NULL;

    while (current != NULL && strcmp(name, current->name) > 0) { // Correção aqui
        prev = current;
        current = current->next;
    }

    prev->next = new_node_name;
    new_node_name->next = current;

    return head;
}

names* remove_names(names* head, int item) {
    if (head == NULL) return head;
    names* prev = NULL;
    names* current = head;

    while (current != NULL && current->item != item) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return head;

    if (prev == NULL) head = current->next;
    else prev->next = current->next;
    free(current);
    return head;
}

int names_index(names* head, char name[]) {
    names* current = head;
    while (current != NULL && strcmp(current->name, name) != 0) current = current->next;
    if (current != NULL) return (current->item);
    return -1;
}

void DFS(graph* graph, names* head, int size) {
    while (head != NULL) {
        names* current = head;
        names* aux2 = NULL;
        int remove_count = 0; // Contador de nós removidos

        while (current != NULL) {
            int index = current->item;
            if (graph->list[index] == NULL) {
                adj_list* new_node = create_adj_list(NULL, index);
                graph->list[index] = new_node;
                aux2 = add_names(aux2, current->name, index);
            }
            current = current->next;
        }

        names* current_print = aux2;
        while (current_print != NULL) {
            printf("%s\n", current_print->name);
            current_print = current_print->next;
        }

        current = aux2;
        while (current != NULL) {
            int index = current->item;
            for (int i = 0; i < size; i++) {
                graph->list[i] = remove_item(graph->list[i], index);
            }
            graph->list[index] = NULL; // Remover referência ao nó
            graph->visited[index] = 1; // Marcar nó como visitado
            head = remove_names(head, index);
            current = current->next;
            remove_count++;
        }

        if (remove_count == 0) break; // Condição de parada quando nenhum nó foi removido
    }
}

int main() {
    int cases;

    while (scanf("%d", &cases) != EOF) {
        int current_size = 0;

        names* names = NULL;
        graph* graph = create_graph();

        char A[MAX_NAMES_SIZE], B[MAX_NAMES_SIZE];

        for (int i = 0; i < cases; i++) {
            scanf("%s %s", A, B);

            int i1 = names_index(names, A);
            if (i1 == -1) {
                names = add_names(names, A, current_size);
                i1 = current_size;
                current_size++;
            }

            int i2 = names_index(names, B);
            if (i2 == -1) {
                names = add_names(names, B, current_size);
                i2 = current_size;
                current_size++;
            }

            graph->list[i1] = create_adj_list(graph->list[i1], i2);
        }
        DFS(graph, names, current_size);
    }
    return 0;
}
