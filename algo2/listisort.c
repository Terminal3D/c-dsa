#include <stdio.h>
#include <stdlib.h>

struct Elem {
    struct Elem *prev, *next;
    long long v;
};

void see_list(struct Elem *start){
    start = start->next;
    while(start->v != -1000000000){
        printf("%lld ", start->v);
        start = start->next;
    }
}

int main() {
    long long n, start_elem = -1000000000;
    scanf("%lld", &n);
    struct Elem* list = malloc(sizeof(struct Elem));
    struct Elem* list_start = list;
    list->v = start_elem;
    list->next = list;
    list->prev = list;
    for(long long i = 0 ; i < n ; i++){
        long long v;
        scanf("%lld", &v);
        struct Elem *new_element = malloc(sizeof(struct Elem));
        new_element->v = v;
        new_element->prev = list;
        new_element->next = list->next;
        list->next = new_element;
        list = new_element;
        list->next->prev = list;
    }
    list = list_start;
    struct Elem *step_elem = list->next->next;
    while(step_elem->v != start_elem){
        struct Elem *temp = step_elem->prev;
        struct Elem *next = step_elem->next;
        while(temp->v > step_elem->v)
            temp = temp->prev;
        step_elem->prev->next = step_elem->next;
        step_elem->next->prev = step_elem->prev;
        step_elem->prev = temp;
        step_elem->next = temp->next;
        temp->next->prev = step_elem;
        temp->next = step_elem;
        step_elem = next;
    }
    see_list(list_start);
    step_elem = list_start->next;
    while(step_elem != list_start){
        struct Elem *next = step_elem->next;
        free(step_elem);
        step_elem = next;
    }
    free(list_start);
    return 0;
}