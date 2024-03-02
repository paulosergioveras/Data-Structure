#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct binary_tree{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
}bt;

bt *create_tree(int item){
    bt *new_node = (bt*)calloc(1, sizeof(bt));
    new_node->item = item;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

bt *build_tree(char str[], int *index){

    ////verifica se tem parentese fechado
    //subarvore vazia

    if(str[*index] == '(' && str[*index + 1] == ')'){ 
        (*index) += 2;
        return NULL;
    }else if(str[*index] == '('){
        (*index)++;
    }

    //array com caracteres numericos
    char numbers[1000];

    int i = 0;

    //esse loop vai verificar se o caracter é um numero
    //primeiro ele vai rodar enquanto for diferente de pararentes
    //depois verifica se é espaço
    //se nao for nenhum desses dois, sera um caracter numerico
    //vai armazenar em numbers[i] o caracter da str
    while(str[*index] != '(' && str[*index] != ')'){
        if(str[*index] == ' ') (*index)++;
        else{
            numbers[i] = str[*index];
            (*index)++;
            i++;
        }
    }

    numbers[i] = '\0';
    int items = atoi(numbers); //converte a str para numeros inteiros
    bt *node = create_tree(items); //cria um novo nó

    //chama recursivamente criando as sub-árvores:
    node->left = build_tree(str, index);
    node->right = build_tree(str, index);

    if(str[*index] == ')'){
        (*index)++;
    }
    return node;
}

int complete(bt *tree, int *total_nodes, int *one_child){
    if(tree == NULL) return 0;

    int left_nodes = complete(tree->left, total_nodes, one_child);
    int right_nodes = complete(tree->right, total_nodes, one_child);

    (*total_nodes)++;

    //verificar se tem apenas um filho
    //ou seja, se o da esquerda tem item e o da direita nao
    //e se o da esquerda nao tem item e o da direita tem
    //se tiver apenas um filho, coloca os items dos do nó dentro do array de one_child

    if((tree->left != NULL && tree->right == NULL) || (tree->left == NULL && tree->right != NULL)){
        one_child[(*one_child)++] = tree->item;
    }

    return left_nodes + right_nodes + 1;
    //retorna a quantidade total de nós
}


int main(){
    char tree[1000]; //arvore
    fgets(tree, 1000, stdin); //leitura da arvore
    int size_tree = strlen(tree); //tamanho da arvore
    char new_tree[1000];

    //no final desse loop, terei new_tree sem os espaços em branco:
    int j = 0;
    for(int i = 0; i < size_tree; i++){ //percorrer a arvore   
        if(tree[i] != ' '){ //se o char nao for um espaço
            //copia o item do caracter para a new_tree
            new_tree[j] = tree[i];
            j++;
        }
    }

    int i = 0;
    bt *root = build_tree(new_tree, &i);

    int total_node = 0;
    int one_child[1000];
    int one_child_count = 0;

    int node_count = complete(root, &total_node, one_child);

    if(node_count == total_node){
        printf("completa\n");
        printf("total de nos: %d\n", total_node);
    }
    else{
        printf("nao completa\n");
        printf("nos com um filho:");

        for(int i = 0; i < one_child_count; i++){
            printf(" %d\n", one_child[i]);
        }
    }

    return 0;
}