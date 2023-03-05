#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Wrong input!");
        return 1;
    }

    char* s = argv[1];
    int len = (int) strlen(s);
    int* pi = calloc(len, sizeof(int));


    pi[0] = 0;
    for (int i = 1, j = 0; i < len; i++) {
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }

    for (int i = 1; i < len; i++) {
        const int period = i + 1 - pi[i];
        if (pi[i] > 0 && (i + 1) % period == 0) {
            printf("%d %d\n", i + 1, (i + 1) / period);
        }
    }

    free(pi);
    return 0;
}
