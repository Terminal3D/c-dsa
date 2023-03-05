#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem {
    struct Elem *next;
    char *word;
};

struct Elem *bsort(struct Elem *list);
void clear(struct Elem *list);

int main() {
    char s[1000];
    struct Elem *list = NULL, *p;

    fgets(s, 1000, stdin);

    char *token = strtok(s, " \n");

    while (token != NULL) {
        p = (struct Elem *) malloc(sizeof(struct Elem));
        p->word = (char *) malloc(sizeof(char) * strlen(token) + 1);
        strcpy(p->word, token);
        p->next = list;
        list = p;
        p = NULL;
        token = strtok(NULL, " \n");
    }
    p = NULL;
    list = bsort(list);

    while (list != NULL) {
        printf("%s ", list->word);
        list = list->next;
    }
    clear(list);
    free(p);
    free(list);
    return 0;
}

void clear(struct Elem *list){
    if (list == NULL)
        return;

    struct Elem *current = list;
    while (current->next != NULL)
    {
        free(current->word);
        free(current);
        current = current->next;
    }
    free(current->word);
    free(current);
}

struct Elem *bsort(struct Elem *list)
{
    struct Elem *current = list;
    int changed = 1;

    while(changed)
    {
        changed = 0;
        current = list;
        while (current != NULL && current->next != NULL)
        {
            if (strlen(current->next->word) < strlen(current->word))
            {
                char *temp = current->word;
                current->word = current->next->word;
                current->next->word = temp;
                changed = 1;
            }
            current = current->next;
        }
    }
    return list;
}