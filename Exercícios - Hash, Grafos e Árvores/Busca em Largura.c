#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10000
#define MAX_SIZE 10000

typedef struct adj_list{
    int item;
    struct adj_list *next;
}adj_list;

typedef struct queue{
    int item[MAX_QUEUE_SIZE];
    int head, tail, current_size, capacity;
}queue;

typedef struct graph{
    adj_list *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
    int distance[MAX_SIZE];
}graph;

int is_empty(queue *queue){
    return (queue->current_size == 0);
}

adj_list *create_adj_list(int item){
    adj_list *new_adj_list = (adj_list*)malloc(sizeof(new_adj_list));
    new_adj_list->item = item;
    new_adj_list->next = NULL;
    return new_adj_list;
}

queue *create_queue(){
    queue *new_queue = (queue*)malloc(sizeof(queue));
    new_queue->current_size = new_queue->head = 0;
    new_queue->tail = MAX_QUEUE_SIZE - 1;
    return new_queue;
}

graph* create_graph(){
    graph *new_graph = (graph*)malloc(sizeof(graph));
    for (int i = 1; i <= MAX_SIZE - 1; i++) {
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = 0;
        new_graph->distance[i] = 0;
    }
    return new_graph;
}

void enqueue(queue *queue, int item){
    if(queue->current_size >= MAX_QUEUE_SIZE) printf("QUEUE OVERFLOW!\n");
    else{
        queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;//garante que ta dentro da fila
        queue->item[queue->tail] = item;//coloca o item na posição atual de tail da queue
        queue->current_size++;
    }
}

int dequeue(queue *queue){
    if(is_empty(queue)){
        printf("EMPTY QUEUE\n");
        return -1;
    }
    else{
        int item = queue->item[queue->head]; 
        queue->head = (queue->head + 1) % MAX_QUEUE_SIZE; // garante que dentro da fila
        queue->current_size--;
        return item;
    }
}

void add_edge(graph *graph, int vertex1, int vertex2){
    adj_list *vertex = create_adj_list(vertex2); //cria um nó do vertex
    vertex->next = graph->vertices[vertex1]; //coloco esse nó para ser o head da lista do vertice
    graph->vertices[vertex1] = vertex;
}

void bfs(graph *graph, int source){
    queue *queue = create_queue();
    int value_dequeued; //valores que seram desenfileirados
    adj_list * adj_list = graph->vertices[source];
    graph->visited[source] = 1; //digo que o vertice ja foi visitado
    enqueue(queue, source); //coloco o item a ser procurado na lista
    while (!is_empty(queue)){ //enquanto a lista nao for vazia
        value_dequeued = dequeue(queue); //desenfilera um vertice
        adj_list = graph->vertices[value_dequeued];//vertice que foi desenfileirado e colocado na lista
        while (adj_list != NULL){
            if (!graph->visited[adj_list->item]){ //percorre os vizinhos do vertice desenfileirado
                printf("Iniciando busca em largura a partir de %d\n", adj_list->item);
                graph->visited[adj_list->item] = 1; //diz que o vertice foi visitado
                enqueue(queue, adj_list->item); //continua a bfs a partir desse vertice que foi visitado
            }
            adj_list = adj_list->next;
        }
    }
    for(int i = 0; i < MAX_SIZE; i++){
        graph->visited[i] = 0;
    }
}

void bfs_distance(graph *graph, int source, int destiny, int *current_distance, int *ant){
    queue *queue = create_queue();
    int value_dequeued;
    adj_list *adj_list = graph->vertices[source];
    graph->visited[source] = 1;
    graph->distance[source] = 1; //inicia a distancia do vertice como 1
    enqueue(queue, source);
    while(!is_empty(queue)){
        value_dequeued = dequeue(queue);
        adj_list = graph->vertices[value_dequeued];
        while(adj_list != NULL){
            if(!graph->visited[adj_list->item]){
                if(adj_list->item == destiny){
                    *ant = value_dequeued;
                    *current_distance = graph->distance[value_dequeued];
                }
                graph->distance[adj_list->item] = graph->distance[value_dequeued]+1;
                graph->visited[adj_list->item] = 1;
                enqueue(queue, adj_list->item);
            }
            adj_list = adj_list->next;
        }
    }
    for(int i = 0; i < MAX_SIZE; i++){
        graph->visited[i] = 0;
    }
}

int main(){
    int vertex, edge, cases;
    int count, current_distance = -1, anterior = -1, aux, origin_vertex2, distiny_vertex2, temp, exist;
    int origin_vertex[1000], destiny_vertex[1000];
    int k1[1000], k2[1000];

    graph *graph = create_graph();
    scanf("%d %d %d", &vertex, &edge, &cases);

    for(int i = 0; i < edge; i++){
        scanf("%d %d", &origin_vertex[i], &destiny_vertex[i]);
    }

    //BUBBLE SORT
    //garante que seja adiciona em ordem crescente dentro do grafo
    for(int i = 0; i < edge; i++){
        for(int j = 0; j < edge-1; j++){
            if(destiny_vertex[j] < destiny_vertex[j+1]){
                aux = destiny_vertex[j];
                destiny_vertex[j] = destiny_vertex[j+1];
                destiny_vertex[j+1] = aux;
                aux = origin_vertex[j];
                origin_vertex[j] = origin_vertex[j+1];
                origin_vertex[j+1] = aux;
            }
        }
    }

    for(int i = 0; i < edge; i++){
        add_edge(graph, origin_vertex[i], destiny_vertex[i]);
    }

    for(int i = 0; i < cases; i++){
        exist = 0;
        count = 0;
        scanf("%d %d", &origin_vertex2, &distiny_vertex2);

        printf("--------\n\n");
        printf("Caso de Teste #%d - BFS(%d)\n\n", i+1, origin_vertex2);
        printf("Iniciando busca em largura a partir de %d\n", origin_vertex2);
        bfs(graph, origin_vertex2);
        printf("\n");

        for(int j = 0; j <= vertex-1; j++){ //percorre os vertices do grafo
            if(origin_vertex2 == j){ //verifica se é o vertice de origem
                current_distance = 0;
                anterior = -1;
            }
            else bfs_distance(graph, origin_vertex2, j, &current_distance, &anterior);

            if(current_distance == -1 && anterior != -1) printf("%d | - | %d\n", j, anterior); //o vertice nao é alcançavel
            else if(current_distance != -1 && anterior == -1) printf("%d | %d | -\n", j, current_distance); //nao tem anterior definido
            else if(current_distance == -1 && anterior == -1) printf("%d | - | -\n", j);//vertice nao encontrado
            else printf("%d | %d | %d\n", j, current_distance, anterior);  //vertice encontrado
            
            k1[j] = anterior;
            current_distance = -1;
            anterior = -1;
        }

        printf("\n");
        temp = k1[distiny_vertex2];
        k2[count] = distiny_vertex2;
        count++;

        while(1){
            k2[count] = temp;
            count++;
            if(temp == -1) break;
            
            if(temp == origin_vertex2){
                exist = 1;
                break;
            }

            temp = k1[temp];
        }
        
        if(exist == 0) printf("Sem caminho entre %d e %d\n", origin_vertex2, distiny_vertex2);
        else{
            printf("Caminho entre %d e %d:", origin_vertex2, distiny_vertex2);
            for(int j = count-1; j >= 0; j--){
                if(j == 0) printf(" %d", k2[j]);
                else printf(" %d =>", k2[j]);
                
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("--------");
    return 0;
}
