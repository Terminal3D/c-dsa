#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 128

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

int *delta1(char *S) {
    int length_s = (int) strlen(S);
    int a = 0;
    int *delta1 = (int *) calloc(SIZE, sizeof(int));

    while (a < SIZE) {
        delta1[a] = length_s;
        a++;
    }
    int j = 0;

    while (j < length_s) {
        delta1[S[j]] = length_s - j - 1;
        ++j;
    }

    return delta1;
}

int *suffix(char *S) {
    int length_s = (int)strlen(S);

    int *sigma = (int *) calloc(length_s, sizeof(int));
    int t = length_s - 1;

    sigma[length_s - 1] = t;

    int i = length_s - 2;

    while (i >= 0) {
        while ((t < length_s - 1) && (S[t] != S[i])) {
            t = sigma[t + 1];
        }
        if (S[t] == S[i]) {
            t--;
        }
        sigma[i] = t;
        i--;
    }

    return sigma;
}

int *delta2(char *S) {
    int lenS = (int) strlen(S);

    int *delta2 = (int *) malloc(sizeof(int) * lenS);
    int *sigma = suffix(S);
    int i = 0;
    int t = sigma[0];

    while (i < lenS) {
        while (t < i) {
            t = sigma[t + 1];
        }
        delta2[i] = -i + t + lenS;
        ++i;
    }
    i = 0;

    while (i < lenS - 1) {
        t = i;
        while (t < lenS - 1) {
            t = sigma[t + 1];
            if (S[i] != S[t]) {
                delta2[t] = -(i + 1) + lenS;
            }
        }
        i++;
    }

    free(sigma);

    return delta2;
}

void bm_subst(char *S, char *T) {
    int i;
    int lenS = (int) strlen(S);
    int lenT = (int) strlen(T);

    int *delta1_arr = delta1(S);
    int *delta2_arr = delta2(S);
    int k = lenS - 1;

    while (k < lenT) {
        i = lenS - 1;
        while (T[k] == S[i]) {
            if (i == 0) {
                printf("%d ", k);
                break;
            }
            i--;
            k--;
        }
        k +=  MAX(delta1_arr[(int) T[k]], delta2_arr[i]);
    }

    free(delta1_arr);
    free(delta2_arr);
}

int main(int argc, char **argv) {
    bm_subst(argv[1], argv[2]);

    return 0;
}
