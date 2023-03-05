#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int minLength(char** words, int n) {
    int length = 0;
    for (int i = 0; i < n; i++) {
        length += (int)strlen(words[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int len1 = (int)strlen(words[i]);
            int len2 = (int)strlen(words[j]);
            for (int k = 1; k <= min(len1, len2); k++) {
                if (strncmp(words[i] + len1 - k, words[j], k) == 0) {
                    length -= k;
                }
            }
        }
    }
    return length;
}

int main() {
    int n;
    scanf("%d", &n);
    char** words = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        words[i] = malloc(256 * sizeof(char));
        scanf("%s", words[i]);
    }
    printf("%d\n", minLength(words, n));
    for (int i = 0; i < n; i++) {
        free(words[i]);
    }
    free(words);
    return 0;
}