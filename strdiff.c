#include <string.h>


int strdiff(char *a, char *b) {
    int size_a = (int) strlen(a);
    int counter = 0;
    int u;
    int axb;
    for (int i = 0; i <= size_a; i++) {
        if ((a[i] ^ b[i]) == 0)
            counter += 8;
        else {
            axb = (a[i] ^ b[i]);
            for (int j = 0; j < 8; j++) {
                u = (1 << j);
                if ((u & axb) == u)
                    return counter;
                else
                    counter++;
            }
        }
    }

    return -1;
}

