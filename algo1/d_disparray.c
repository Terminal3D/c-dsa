#include <stdio.h>
#include <stdlib.h>

#define True 1

typedef struct Elem {
    int data;
    int key;
} el;

typedef struct Node {
    el elem;
    struct Node *next;
} node;

int h_func(int pos, int n) {
    return pos % n;
}

int main() {
    int n;
    scanf("%i", &n);
    node **array = calloc(n, sizeof(node));
    char op[7];
    while (True) {
        scanf("%s", op);
        if (op[0] == 'A' && op[1] == 'T') {
            int key;
            scanf("%i", &key);
            int h_key = h_func(key, n);
            node *temp = array[h_key];
            if (temp == NULL)
                printf("0\n");
            else {
                while (temp != NULL && temp->elem.key != key)
                    temp = temp->next;
                if (temp == NULL)
                    printf("0\n");
                else
                    printf("%i\n", temp->elem.data);
            }
        } else if (op[0] == 'A') {
            int key, value;
            scanf("%i %i", &key, &value);
            int h_key = h_func(key, n);
            if (value == 0) {
                node *temp = array[h_key];
                node *temp_prev = NULL;
                if (temp == NULL || temp->elem.data == 0)
                    temp = NULL;
                else {
                    while (temp->elem.key != key) {

                        temp_prev = temp;
                        temp = temp->next;
                        if (temp == NULL)
                            break;
                    }
                    if (temp != NULL && temp->next != NULL && temp_prev == NULL) {
                        array[h_key] = temp->next;
                        free(temp);
                    } else if (temp_prev == NULL && temp != NULL && temp->next == NULL) {
                        free(temp);
                        array[h_key] = NULL;
                    } else if (temp_prev != NULL && temp != NULL && temp->next == NULL) {
                        temp_prev->next = NULL;
                        free(temp);
                    } else if (temp != NULL && temp->next != NULL) {
                        temp_prev->next = temp->next;
                        free(temp);
                    }


                }
            } else {
                node *temp = array[h_key];
                if (temp == NULL || temp->elem.data == 0) {
                    array[h_key] = calloc(1, sizeof(node));
                    array[h_key]->elem.data = value;
                    array[h_key]->elem.key = key;
                    array[h_key]->next = NULL;
                } else {
                    while (temp != NULL && temp->elem.key != key)
                        temp = temp->next;
                    if(temp != NULL){
                        temp->elem.data = value;
                    }else {
                        node *new_node = calloc(1, sizeof(node));
                        new_node->elem.key = key;
                        new_node->elem.data = value;
                        new_node->next = NULL;
                        temp->next = new_node;
                    }
                }


            }
        } else break;
    }
    for(int i = 0 ; i < n ; i++){
        while(array[i] != NULL){
            node* temp = array[i];
            array[i] = array[i]->next;
            free(temp);
        }
    }
    free(array);
    return 0;
}