#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}


void buildTree(int *arr, int *tree, int node, int start, int end) {
    if (start == end)
        tree[node] = arr[start];
    else {
        int mid = (start + end) / 2;
        buildTree(arr, tree, 2 * node + 1, start, mid);
        buildTree(arr, tree, 2 * node + 2, mid + 1, end);
        tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]);
    }
}


int query(int *tree, int start, int end, int node, int a, int b) {
    if ((a == start) && (b == end))
        return tree[node];
    else if ((a > end) || (b < start))
        return 0;
    else {
        int mid = (start + end) / 2;
        return gcd(query(tree, start, mid, 2 * node + 1, a, MIN(b, mid)),
                   query(tree, mid + 1, end, 2 * node + 2, MAX(a, mid + 1), b));
    }
}


int main() {
    int n, m, temp;
    scanf("%i", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%i", &temp);
        arr[i] = abs(temp);
    }

    int *tree = calloc(4 * n, sizeof(int));
    buildTree(arr, tree, 0, 0, n - 1);
    scanf("%i", &m);
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%i %i", &l, &r);
        printf("%i\n", query(tree, 0, n - 1, 0, l, r));
    }
    free(tree);
    return 0;
}