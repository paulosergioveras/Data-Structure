#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct binary_tree{
    int item;
    struct binary_tree *right;
    struct binary_tree *left;
}bt;

bt *create_bt_node(int item){
    bt *new_bt_node = (bt*)calloc(1, sizeof(bt));
    new_bt_node->item = item;
    new_bt_node->right = new_bt_node->left = NULL;
    return new_bt_node;
}

//função para verificar se é uma bt:

int is_tree(bt *root, int min, int max){
    if(root == NULL) return 1;

    if(root->item <= min || root->item >= max) return 0;

    return is_tree(root->left, min, root->item) && is_tree(root->right, root->item, max);
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
    bt *node = create_bt_node(items); //cria um novo nó

    //chama recursivamente criando as sub-árvores:
    node->left = build_tree(str, index);
    node->right = build_tree(str, index);

    if(str[*index] == ')'){
        (*index)++;
    }
    
    return node;
}

int main(){
    char tree[1000]; //arvore

    fgets(tree, 1000, stdin); //leitura da arvore
 
    int size_tree = strlen(tree); //tamanho da arvore

    char new_tree[1000];

    //no final desse loop, terei new_tree sem os espaços em branco:
    int j = 0;
    for(int i = 0; i < size_tree; i++) //percorrer a tree
    {   
        if(tree[i] != ' ')//se o char nao for um espaço
        {
            //copia o item do caracter para a new_tree
            new_tree[j] = tree[i];
            j++;
        }
    }

    int i = 0;
    bt *root = build_tree(new_tree, &i);

    if(is_tree(root, INT_MIN, INT_MAX)){
        printf("VERDADEIRO\n");
    }else{
        printf("FALSO\n");
    } 

    return 0;
}