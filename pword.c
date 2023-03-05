#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_prefix_function(char *s, int s_len, int *prefix) {
    prefix[0] = 0;
    int k = 0;
    for (int i = 1; i < s_len; i++) {
        while (k > 0 && s[k] != s[i]) {
            k = prefix[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        prefix[i] = k;
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Please enter two strings S and T as command-line arguments.\n");
        return 0;
    }
    char *s = argv[1];
    char *t = argv[2];
    int s_len = (int) strlen(s);
    int t_len = (int) strlen(t);
    int *prefix = malloc(s_len * sizeof(int));
    compute_prefix_function(s, s_len, prefix);
    int j = 0;
    for (int i = 0; i < t_len; i++) {
        while (j > 0 && t[i] != s[j]) {
            j = prefix[j - 1];
        }
        if (t[i] == s[j]) {
            j++;
        }
        if (j == s_len) {
            j = prefix[j - 1];
        }
    }

    if (j == 0) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    free(prefix);
    return 0;
}