#include <stdio.h>
#include <stdlib.h>


void insert_sort(int *a, int i, int j) {
    for (int k = i + 1; k <= j; k++) {
        for (int local = k - 1; local >= i; local--) {
            if (a[local] * a[local] > a[local + 1] * a[local + 1]) {
                int temp = a[local + 1];
                a[local + 1] = a[local];
                a[local] = temp;

            }
        }
    }

}

void merge_sort(int i, int j, int *a, int *aux) {
    if (i < j) {
        if (j - i + 1 < 5) {
            insert_sort(a, i, j);
        } else {
            int mid = (i + j) / 2;

            merge_sort(i, mid, a, aux);
            merge_sort(mid + 1, j, a, aux);
            int pointer_left = i;
            int pointer_right = mid + 1;
            int k;

            for (k = i; k <= j; k++) {
                if (pointer_left == mid + 1) {
                    aux[k] = a[pointer_right];
                    pointer_right++;
                } else if (pointer_right == j + 1) {
                    aux[k] = a[pointer_left];
                    pointer_left++;
                } else if (abs(a[pointer_left]) <= abs(a[pointer_right])) {
                    aux[k] = a[pointer_left];
                    pointer_left++;
                } else {
                    aux[k] = a[pointer_right];
                    pointer_right++;
                }
            }
            for (k = i; k <= j; k++)
                a[k] = aux[k];
        }
    }
}


int main() {
    int n, i;

    scanf("%d", &n);
    int a[n], aux[n];
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    merge_sort(0, n - 1, a, aux);

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}