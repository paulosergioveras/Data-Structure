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

int found_num(bt *tree, int n, int depth){
    if(tree == NULL) return -1;

    if(tree->item == n) return depth;

    int left_dep = found_num(tree->left, n, depth+1);
    if(left_dep != -1) return left_dep;

    int right_dep = found_num(tree->right, n, depth+1);
    return right_dep;
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

    int n; //item a ser encontrado
    scanf("%d", &n);

    int depth = found_num(root, n, 0);

    if(depth == -1) printf("NAO ESTA NA ARVORE\n-1\n");
    else{
        printf("ESTA NA ARVORE\n");
        printf("%d\n", depth);
    }

    return 0;
}