#include <stdio.h>
#include <stdlib.h>

int abs_val(int x) {
    return (x ^ (x >> 31)) - (x >> 31);
}

int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;
    if (~a & 1) {
        if (b & 1) return gcd(a >> 1, b);
        else return gcd(a >> 1, b >> 1) << 1;
    }
    if (~b & 1) return gcd(a, b >> 1);
    if (a > b) return gcd((a - b) >> 1, b);
    return gcd((b - a) >> 1, a);
}

int log2n(int n) {
    return 31 - __builtin_clz(n);
}

void build(int *arr, int n, int **st) {
    int j, i;
    int log2 = log2n(n);
    for (i = 0; i < n; i++) {
        st[i][0] = arr[i];
    }
    for (j = 1; j <= log2; j++) {
        for (i = 0; i + (1 << j) - 1 < n; i++) {
            st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r, int **st) {
    int k = log2n(r - l + 1);
    return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
    int n, m, i;
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    int **st = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        st[i] = malloc((log2n(n) + 1) * sizeof(int));
    for (i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        arr[i] = abs_val(temp);
    }
    build(arr, n, st);
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", query(l, r, st));
    }
    for (i = 0; i < n; i++)
        free(st[i]);
    free(arr);
    free(st);
    return 0;
}
