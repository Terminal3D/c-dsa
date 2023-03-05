include <string.h>
#include <stdio.h>
int wcount(char* s) {
    int count = 0;
    int len = strlen(s);
    int flag = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] != ' ') {
            if (flag == 0) {
                count++;
                flag = 1;
            }
        } else {
            flag = 0;
        }
    }
    return count;
}
