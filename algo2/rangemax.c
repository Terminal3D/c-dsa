#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define True 1


void buildTree(int *arr, int *tree, int node, int start, int end, int n) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        buildTree(arr, tree, 2 * node + 1, start, mid, n);
        buildTree(arr, tree, 2 * node + 2, mid + 1, end, n);
        tree[node] = MAX(tree[2 * node + 1], tree[2 * node + 2]);
    }
}


int query(int *tree, int start, int end, int node, int a, int b) {
    int result = INT_MIN;

    while (True) {
        if ((a == start) && (b == end)) {
            result = tree[node];
            break;
        }

        int mid = (start + end) / 2;
        if (b <= mid) {
            end = mid;
            node = 2 * node + 1;
        } else if (a > mid) {
            start = mid + 1;
            node = 2 * node + 2;
        } else {
            int left_node = 2 * node + 1;
            int right_node = 2 * node + 2;
            int left_result = query(tree, start, mid, left_node, a, MIN(b, mid));
            int right_result = query(tree, mid + 1, end, right_node, MAX(a, mid + 1), b);
            result = MAX(left_result, right_result);
            break;
        }
    }

    return result;
}



void update(int *arr, int *tree, int node, int start, int end, int i, int n) {
    if (start == end) {
        tree[node] = arr[start];

    } else {
        int mid = (start + end) / 2;
        if (i <= mid) {
            update(arr, tree, 2 * node + 1, start, mid, i, n);
        } else {
            update(arr, tree, 2 * node + 2, mid + 1, end, i, n);
        }
        tree[node] = MAX(tree[2 * node + 1], tree[2 * node + 2]);
    }

}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int *tree = calloc(4 * n, sizeof(int));

    buildTree(arr, tree, 0, 0, n - 1, n);

    while (True) {
        char op[4];
        scanf("%s", op);
        if (op[0] == 'M') {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", query(tree, 0, n - 1, 0, a, b));
        } else if (op[0] == 'U') {
            int i, v;
            scanf("%d %d", &i, &v);
            arr[i] = v;
            update(arr, tree, 0, 0, n - 1, i, n);
        } else {
            break;
        }
    }
    free(tree);
    return 0;

}