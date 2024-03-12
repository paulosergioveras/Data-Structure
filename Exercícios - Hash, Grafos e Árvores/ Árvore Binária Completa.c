#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct binary_tree {
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} bt;

bt *create_tree(int item) {
    bt *new_node = (bt *)calloc(1, sizeof(bt));
    new_node->item = item;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

bt *build_tree(char str[], int *index) {
    if (str[*index] == '(' && str[*index + 1] == ')') {
        (*index) += 2;
        return NULL;
    } else if (str[*index] == '(') {
        (*index)++;
    }

    char numbers[1000];
    int i = 0;

    while (str[*index] != '(' && str[*index] != ')') {
        if (str[*index] == ' ')
            (*index)++;
        else {
            numbers[i] = str[*index];
            (*index)++;
            i++;
        }
    }

    numbers[i] = '\0';
    int items = atoi(numbers);
    bt *node = create_tree(items);
    node->left = build_tree(str, index);
    node->right = build_tree(str, index);

    if (str[*index] == ')') {
        (*index)++;
    }

    return node;
}

int is_complete(bt *root){
    if(root == NULL) return 1;
    if(root->left == NULL && root->right != NULL) return 0; //significa que tem um filho na direita
    if(root->left != NULL && root->right == NULL) return 0; //significa que tem um filho na esquerda
    return is_complete(root->left) && is_complete(root->right); //percorre recursivamente os nós da direita e esquerda
}

//vai printar os nós que tem apenas um filho
void print_one_child(bt *root){
    if(root == NULL) return; 

    print_one_child(root->left);

    if((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)){
        printf("%d ", root->item);
    }

    print_one_child(root->right);
}

//conta a quantidade total de nós da arvore
int count_nodes(bt *root){
    if(root == NULL) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}


int main() {
    char tree[1000]; //arvore
    fgets(tree, 1000, stdin); //leitura da arvore
    int size_tree = strlen(tree); //tamanho da arvore
    char new_tree[1000];

    //no final desse loop, terei new_tree sem os espa�os em branco:
    //percorrer a arvore  
    //se o char nao for um espa�o
    //copia o item do caracter para a new_tree

    int j = 0;
    for(int i = 0; i < size_tree; i++){ 
        if(tree[i] != ' '){
            new_tree[j] = tree[i];
            j++;
        }
    }

    int i = 0;
    bt *root = build_tree(new_tree, &i);

    printf("%s\n", is_complete(root) ? "completa" : "nao completa");

    if(is_complete(root)){
        printf("total de nos: %d\n", count_nodes(root));
    }else{
        printf("nos com um filho: ");
        print_one_child(root);
    }
    return 0;
}
