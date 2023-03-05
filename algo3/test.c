#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem {
    struct Elem *next;
    char *word;
};

struct Elem *add_node(struct Elem *list, char *word) {
    struct Elem *new_node = malloc(sizeof(struct Elem));
    new_node->word = word;
    new_node->next = NULL;
    if (list == NULL) {
        list = new_node;
    } else {
        struct Elem *current = list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return list;
}

struct Elem *bsort(struct Elem *list) {
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        struct Elem* element = list;
        while (element && element->next) {
            if (strlen(element->word) > strlen(element->next->word)) {
                char* temp = element->word;
                element->word = element->next->word;
                element->next->word = temp;
                swapped = 1;
            }
            element = element->next;
        }
    }
    return list;
}

int main() {
    struct Elem *list = NULL, *prev = NULL;
    char c, *word = NULL;
    int word_len = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n') {
            if (word_len > 0) {
                word[word_len] = '\0';
                list = add_node(list, word);
                prev = list;
                word = NULL;
                word_len = 0;
            }
        } else {
            if (word == NULL) {
                word = malloc(1001);
            }
            word[word_len++] = c;
        }
    }
    if (word_len > 0) {
        word[word_len] = '\0';
        list = add_node(list, word);
        prev = list;
    }
    list = bsort(list);
    while (list != NULL) {
        printf("%s ", list->word);
        struct Elem *temp = list;
        list = list->next;
        free(temp->word);
        free(temp);
    }
    printf("\n");
    return 0;
}
