#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"

struct Elem {
    char *word;
    struct Elem *next;
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

void print_list(struct Elem *list) {
    while (list != NULL) {
        printf("%s ", list->word);
        list = list->next;
    }
}

void free_list(struct Elem *list) {
    while (list != NULL) {
        struct Elem *tmp = list;
        list = list->next;
        free(tmp->word);
        free(tmp);

    }
}

char **word_separate(char *s) {
    char **words = malloc(1000 * sizeof(char));
    char *pch = strtok(s, " ");
    int len;
    int total = 0;
    int i = 0;
    while (pch != NULL) {

        len = (int) strlen(pch);
        total += len;
        words[i] = pch;
        i++;
        pch = strtok(NULL, " ");

    }
    return words;
}

int main() {
    char* sentence = calloc(1001, sizeof(char));
    gets(sentence);
    struct Elem *list = NULL;
    char** words = word_separate(sentence);

    bsort(list);
    print_list(list);
    free_list(list);
    return 0;
}


