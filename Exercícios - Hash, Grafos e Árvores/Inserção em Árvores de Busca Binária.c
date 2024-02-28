#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct binary_tree{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
}bt;

bt *start_tree(){
    return NULL;
}

bt *create_bt_node(int item){
    bt *new_bt_node = (bt*)calloc(1, sizeof(bt));
    new_bt_node->item = item;
    new_bt_node->right = new_bt_node->left = NULL;
    return new_bt_node;
}

bt *is_empty(bt *tree){
    return tree == NULL;
}

void print_tree(bt *tree){
    printf(" (");
    if(!is_empty(tree)){
        printf(" %d ", tree->item);
        print_tree(tree->left);
        print_tree(tree->right);
    }
    printf(") ");
}

bt *insert_intree(bt *tree, int item){
    if(tree == NULL) return create_bt_node(item);

    if(item < tree->item){
        tree->left = insert_intree(tree->left, item);
    }
    else{
        tree->right = insert_intree(tree->right, item);
    }
    return tree;
}

int main(){
    bt *tree = start_tree();
    int item;
    
    while(scanf("%d", &item) == 1){
        printf("----\n");
        printf("Adicionando %d\n  ", item);
        tree = insert_intree(tree, item);
        print_tree(tree);
        printf("\n");
    }
    printf("----");
    return 0;
}