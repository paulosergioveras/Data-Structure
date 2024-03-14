#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct bt{
    int item;
    struct bt *left;
    struct bt *right;
    struct bt *parent;
}bt;

//create_bt_node:

bt *create_bt_node(int item){
    bt *new_bt_node = (bt*)malloc(sizeof(bt));
    new_bt_node->item = item;
    new_bt_node->left = NULL;
    new_bt_node->right = NULL;
    new_bt_node->parent = NULL;
    return new_bt_node;
}

//build_tree:

bt *build_tree(char **entrr, bt *parent) {
    if (**entrr == '(') (*entrr)++;

    if (**entrr == ')') {
        (*entrr)++;
        return NULL;
    }

    int item;
    sscanf(*entrr, "%d", &item); //converte diretamente o num da str
    bt *node = create_bt_node(item);
    node->parent = parent;

    //loop para encontrar um caracter que nao é digito, ou seja, percorre todos os numeros
    while (**entrr == '-' || isdigit(**entrr)) {
        (*entrr)++;
    }
    
    node->left = build_tree(entrr, node);
    node->right = build_tree(entrr, node);
    if (**entrr == ')') (*entrr)++;
    return node;
}



//dfs:

void replace(bt *tree1, bt *tree2){
    if(tree1 == NULL) return;

    if(tree1->item == tree2->item && tree1->parent != NULL){
        if(tree1->parent->left == tree1){
            tree1->parent->left = tree2;
        }else{
            tree1->parent->right = tree2;
        }
        
        if (tree2 != NULL) {
            tree2->parent = tree1->parent;
        }
    }

    replace(tree1->left, tree2);
    replace(tree1->right, tree2);
}

//concatenate_tree:

bt *concatenate_tree(bt *tree1, bt *tree2){
    if(tree1 == NULL) return tree2;
    if(tree2 == NULL) return tree1;

    if(tree1->item == tree2->item) return tree2;
    replace(tree1, tree2);

    //se apos a chamada o parent de tree2 for nulo é pq nao encontrou t2 em t1
    if(tree2->parent == NULL){
        bt *aux = tree1;

        while(aux->right != NULL){
            aux = aux->right; //procura o nó mais a direita em t1 para colocar t2
        }

        aux->right = tree2; //conceta t2 ao filho mais a direita de t1
        tree2->parent = aux;
    }
    return tree1;
}

//print_tree:

void print_tree(bt *bt){
    if(bt == NULL){
        printf("()");
    }else{
        printf("(%d", bt->item);
        print_tree(bt->left);
        print_tree(bt->right);
        printf(")");
    }
}

int main(){
    char *entrr = (char*)malloc(100*sizeof(char));
    bt *second_tree = NULL;

    while(1){
        scanf(" %s", entrr);

        if(strcmp(entrr, "()") == 0){
            break;
        }

        bt *first_tree = build_tree(&entrr, NULL);
        second_tree = concatenate_tree(second_tree, first_tree);
    }
    print_tree(second_tree);

    return 0;
}