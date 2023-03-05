#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int* prefix_function(const char* s, int s_len) {
    int* pi = (int*)malloc(s_len * sizeof(int));
    pi[0] = 0;

    for (int i = 1; i < s_len; i++) {
        int j = pi[i - 1];
        while ((j > 0) && (s[j] != s[i])) {
            j = pi[j - 1];
        }
        if (s[j] == s[i]) {
            j++;
        }
        pi[i] = j;
    }

    return pi;
}

void find_all(const char* t, int t_len, const char* s, int s_len) {
    int* pi = prefix_function(s, s_len);

    int j = 0;
    for (int i = 0; i < t_len; i++) {
        while ((j > 0) && (s[j] != t[i])) {
            j = pi[j - 1];
        }
        if (s[j] == t[i]) {
            j++;
        }
        if (j == s_len) {
            printf("%d\n", i - s_len + 1);
            j = pi[j - 1];
        }
    }
    free(pi);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Введите две строки S и T");
        return 0;
    }
    const char* s = argv[1];
    const char* t = argv[2];
    int t_len = (int)strlen(t);
    int s_len = (int)strlen(s);

    find_all(t, t_len, s, s_len);

    return 0;
}


