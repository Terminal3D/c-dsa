#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define True 1

int isHyperdrome(int* arr, int n, int i) {
    if (n == 1) {
        return 1;
    }
    if (i == 0) {
        return arr[i] >= arr[i+1];
    } else if (i == n-1) {
        return arr[i] >= arr[i-1];
    } else {
        return arr[i] >= arr[i-1] && arr[i] >= arr[i+1];
    }
}



void buildTree(int *arr, int *tree, int node, int start, int end, int n) {
    if (start == end) {
        if (isHyperdrome(arr, n, start)) {
            tree[node] = 1;
        } else {
            tree[node] = 0;
        }
        return;

    } else {
        int mid = (start + end) / 2;
        buildTree(arr, tree, 2 * node + 1, start, mid, n);
        buildTree(arr, tree, 2 * node + 2, mid + 1, end, n);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
}


int query(int* tree, int start, int end, int node, int a, int b) {
    if ((a == start) && (b == end))
        return tree[node];
    else if ((a > end) || (b < start))
        return 0;
    else {
        int mid = (start + end) / 2;
        return query(tree, start, mid, 2 * node + 1, a, MIN(b, mid)) +
               query(tree, mid + 1, end, 2 * node + 2, MAX(a, mid + 1), b);
    }
}


void update(int *arr, int *tree, int node, int start, int end, int i, int n) {
    if (start == end) {
        if (isHyperdrome(arr, n, i)) {
            tree[node] = 1;
        } else {
            tree[node] = 0;
        }
        return;
    } else {
        int mid = (start + end) / 2;
        if (i <= mid) {
            update(arr, tree, 2 * node + 1, start, mid, i, n);
        } else {
            update(arr, tree, 2 * node + 2, mid + 1, end, i, n);
        }
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int* tree = calloc(4 * n, sizeof(int));

    buildTree(arr, tree, 0, 0, n - 1, n);

    while (True) {
        char op[6];
        scanf("%s", op);
        if (op[0] == 'P') {
            int a,b;
            scanf("%d %d", &a, &b);
            printf("%d\n", query(tree, 0, n - 1, 0, a, b));
        } else if (op[0] == 'U') {
            int i,v;
            scanf("%d %d", &i, &v);
            arr[i] = v;
            update(arr, tree, 0, 0, n - 1, i, n);
            if (i > 0)
                update(arr, tree, 0, 0, n - 1, i - 1, n);
            if (i < n - 1)
                update(arr, tree, 0, 0, n - 1, i + 1, n);
        } else {
            break;
        }
    }
    free(tree);
    return 0;

}