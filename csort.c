#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char **word_separate(char *s, int *count) {
    char **words = malloc(1000 * sizeof(char));
    char *pch = strtok(s, " ");
    int len;
    int total = 0;
    while (pch != NULL) {

        len = (int) strlen(pch);
        total += len;
        words[(*count)] = pch;
        (*count)++;
        pch = strtok(NULL, " ");

    }
    return words;
}


void csort(char *src, char *dest) {

    int n = 0;
    char **words = word_separate(src, &n);
    int *count = calloc(n, sizeof(int));
    int word_number = 0;
    int len, local_len, local_number;
    while (word_number < n) {
        len = (int) strlen(words[word_number]);
        local_number = word_number;
        while (local_number < n - 1) {
            local_number++;
            local_len = (int) strlen(words[local_number]);
            if (len <= local_len)
                count[local_number]++;
            else
                count[word_number]++;

        }
        word_number++;
    }
    char** words_sorted = malloc(sizeof(char)*1000);
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (1){
            if (count[k] == i) {
                words_sorted[i] = words[k];
                k = 0;
                break;
            }
            k++;
        }

    }

    int loc = 0;
    int i;
    for (i = 0; i < n; i++){
        strcpy(dest + loc, words_sorted[i]);
        loc += (int)strlen(words_sorted[i]);
        if (i != n - 1)
            strcpy(dest + loc, " ");
        loc++;
    }
    free(words);
    free(count);
    free(words_sorted);
}

int main() {
    char* s = calloc(1000, sizeof(char));
    gets(s);
    char* out = calloc(1000, sizeof(char));
    csort(s, out);
    puts(out);
    free(s);
    free(out);
    return 0;
}