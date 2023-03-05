#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void dsort(char* s) {
    int* count = calloc(26, sizeof(int));
    int len = (int)strlen(s);
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }
    int index = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i]; j++) {
            s[index++] = 'a' + i;
        }
    }
    free(count);
}

int main() {
    char s[1000001];
    scanf("%s", s);
    dsort(s);
    printf("%s", s);
    return 0;
}
