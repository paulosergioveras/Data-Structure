node* create_linked_list()
{
    return NULL;
}

int is_empty(node *head)
{
    return (head == NULL);
}

node* add_begin(node *head, int item)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = head;
    return new_node;
}

node* search(node *head, int item)
{
    while(head != NULL)
    {
        if(head->item = item)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

node* add_end(node **head, int new_item){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = new_item;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } 
    else {
        node *current = *head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_node;
    }
}

void print_list(node *head){
    while(head != NULL){
        printf("%d ", head->item);
        head = head->next;
    }
    //printf("\n");
}

void free_list(node *head){
    node *current = head;
    node *next;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

void print_list_reverse(node *head){
    if(head == NULL){
        return;
    }
    print_list_reverse(head->next);
    printf("%d ", head->item);
}