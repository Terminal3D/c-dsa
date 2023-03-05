#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void build_prefix_function(char* str, int* prefix, int str_len) {
    prefix[0] = 0;
    for (int i = 1; i < str_len; ++i) {
        int k = prefix[i - 1];
        while (str[k] != str[i] && k > 0) {
            k = prefix[k - 1];
        }
        if (str[k] == str[i]) {
            k++;
        }
        prefix[i] = k;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 0;
    }
    char* str = argv[1];
    int str_len = (int)strlen(str);
    int* prefix = calloc(str_len, sizeof(int));
    build_prefix_function(str, prefix, str_len);
    for (int i = 1; i < str_len; i++) {

        if (prefix[i] > 0 && ((i + 1) % ((i + 1) - prefix[i])) == 0) {
            printf("%d %d\n", i + 1, (int)((i + 1) / (i + 1 - prefix[i])));

        }
    }
    free(prefix);
    return 0;
}



