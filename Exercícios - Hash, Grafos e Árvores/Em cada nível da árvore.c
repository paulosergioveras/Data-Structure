#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct binary_tree{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
}bt;

typedef struct entr{
    int value;
    int *left_i;
    int *right_i;
}entr;

bt *create_tree(entr *entries, int i){
    if(i == -1) return NULL; 

    bt *new_node = (bt*)malloc(sizeof(bt));
    new_node->item = entries[i].value;
    new_node->right = create_tree(entries, entries[i].right_i);
    new_node->left = create_tree(entries, entries[i].left_i);
    return new_node;
}

int tree_height(bt *bt){
    if(bt == NULL) return 0;

    int left_heitght = tree_height(bt->left);
    int right_height = tree_height(bt->right);
    return (left_heitght > right_height ? left_heitght : right_height) + 1;
}

void find_max_min(bt *bt, int *min, int *max, int level){
    if(bt == NULL) return;
    if(bt->item > max[level]) max[level] = bt->item;
    if(bt->item < min[level]) min[level] = bt->item;
    find_max_min(bt->left, min, max, level+1);
    find_max_min(bt->right, min, max, level+1);
}

int main(){
    int num_entr;
    scanf("%d", &num_entr);
    entr *entries = (entr*)malloc(sizeof(entr) * num_entr);

    for(int i = 0; i < num_entr; i++){
        scanf("%d %d %d", &entries[i].value, &entries[i].right_i, &entries[i].left_i);
    }

    bt *bt = create_tree(entries, 0);
    int height = tree_height(bt);

    int *max_value = (int*)malloc(sizeof(int) * height);
    int *min_value = (int*)malloc(sizeof(int) * height);

    for(int i = 0; i < height; i++){
        max_value[i] = INT_MIN;
        min_value[i] = INT_MAX;
    }
    

   //int *max_value = (int*)calloc(height,sizeof(int));
   //int *min_value = (int*)calloc(height,sizeof(int));

    find_max_min(bt, min_value, max_value, 0);

    for(int i = 0; i < height; i++){
        printf("Nivel %d: Maior = %d, Menor = %d\n", i+1, max_value[i], min_value[i]);
    }

    free(entries);
    free(max_value);
    free(min_value);
    free(bt);

    return 0;
}