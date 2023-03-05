#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int x, int y) {
    return x >= y ? x : y;
}

void compute_delta1(int* delta1, const char* S, int lenS) {
    int a = 0;
    while (a < 256) {
        delta1[a++] = lenS;
    }
    for (int j = 0; j < lenS; ++j) {
        delta1[S[j]] = lenS - j - 1;
    }
}

int* compute_suffix(const char* S, int lenS) {
    int* sigma = (int*) calloc(lenS, sizeof(int));
    int t = lenS - 1;
    sigma[lenS - 1] = t;

    for (int i = lenS - 2; i >= 0; --i) {
        while (t < lenS - 1 && S[t] != S[i]) {
            t = sigma[t + 1];
        }
        if (S[t] == S[i]) {
            --t;
        }
        sigma[i] = t;
    }
    return sigma;
}

void compute_delta2(int* delta2, const char* S, int lenS, int* sigma) {
    int t = sigma[0];
    for (int i = 0; i < lenS; ++i) {
        while (t < i) {
            t = sigma[t + 1];
        }
        delta2[i] = -i + t + lenS;
    }
    for (int i = 0; i < lenS - 1; ++i) {
        t = i;
        while (t < lenS - 1) {
            t = sigma[t + 1];
            if (S[i] != S[t]) {
                delta2[t] = -(i + 1) + lenS;
            }
        }
    }
    free(sigma);
}

void Bm(const char* S, const char* T) {
    int lenS = (int) strlen(S);
    int lenT = (int) strlen(T);
    int delta1[10000];
    compute_delta1(delta1, S, lenS);
    int* delta2 = (int*) malloc(lenS * sizeof(int));
    int* sigma = compute_suffix(S, lenS);
    compute_delta2(delta2, S, lenS, sigma);
    int k = lenS - 1;
    while (k < lenT) {
        int i = lenS - 1;
        while (T[k] == S[i]) {
            if (i == 0) {
                printf("%d ", k);
                break;
            }
            --i;
            --k;
        }
        k += max(delta1[(unsigned char) T[k]], delta2[i]);
    }
    free(delta2);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Wrong input format!");
        return 1;
    }
    Bm(argv[1], argv[2]);
    return 0;
}