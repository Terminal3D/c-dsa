#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_prefix(char* s, int* pi) {
    int len = strlen(s);
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
}

void kmp(char* t, char* s) {
    int t_len = strlen(t);
    int s_len = strlen(s);
    int* pi = (int*) malloc(s_len * sizeof(int));
    compute_prefix(s, pi);
    for (int i = 0, j = 0; i < t_len; i++) {
        while (j > 0 && t[i] != s[j]) {
            j = pi[j - 1];
        }
        if (t[i] == s[j]) {
            j++;
        }
        if (j == s_len) {
            printf("%d ", i - s_len + 1);
            j = pi[j - 1];
        }
    }
    free(pi);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong Input\n");
        return 1;
    }
    char* s = argv[1];
    char* t = argv[2];
    kmp(t, s);
    return 0;
}
