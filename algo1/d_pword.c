#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void isMadeOfPrefix(char* s, char* t) {
    int len_s = (int) strlen(s);
    int* pi = calloc(len_s, sizeof(int));
    pi[0] = 0;
    int m = 0, i = 1;
    while (i < len_s) {
        while ((m > 0) && (s[m] != s[i]))
            m = pi[m - 1];
        if (s[m] == s[i])
            m++;
        pi[i] = m;
        i++;
    }
    int len_t = (int) strlen(t), j = 0;
    for (i = 0; i < len_t; i++) {
        while (j > 0 && t[i] != s[j]) {
            j = pi[j - 1];
        }
        if (t[i] == s[j]) {
            j++;
        }
        if (j == 0) {
            printf("no\n");
            free(pi);
            return;
        }
        if (j == len_s) {
            j = pi[j - 1];
        }

    }
    free(pi);
    printf("yes\n");
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Invalid Input.\n");
        return 0;
    }
    isMadeOfPrefix(argv[1], argv[2]);
    return 0;
}