#include <stdio.h>
#include <string.h>


void kmp(char* t, char* s) {
    int t_len = (int)strlen(t);
    int s_len = (int)strlen(s);
    int pi[s_len];
    pi[0] = 0;
    for (int i = 1, j = 0; i < s_len; i++) {
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    for (int i = 0, j = 0; i < t_len; i++) {
        while (j > 0 && t[i] != s[j]) {
            j = pi[j - 1];
        }
        if (t[i] == s[j]) {
            j++;
        }
        if (j == s_len) {
            printf("%i ", i - s_len + 1);
            j = pi[j - 1];
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Введите S и T\n");
        return 0;
    }
    char* s = argv[1];
    char* t = argv[2];
    kmp(t, s);
    return 0;
}