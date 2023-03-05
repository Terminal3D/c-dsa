#include <stdio.h>
#include <stdlib.h>

void insert_sort(int arr[], int i, int j) {
    for (int k = i + 1; k <= j; k++) {
        for (int l = k - 1; l >= i; l--) {
            if (arr[l] * arr[l] > arr[l + 1] * arr[l + 1]) {
                int temp = arr[l + 1];
                arr[l + 1] = arr[l];
                arr[l] = temp;

            }
        }
    }

}

void merge_sort(int i, int j, int *arr, int *aux) {
    if (i < j) {
        if (j - i + 1 < 5) {
            insert_sort(arr, i, j);
        } else {
            int mid = (i + j) / 2;

            merge_sort(i, mid, arr, aux);
            merge_sort(mid + 1, j, arr, aux);
            int p_l = i;
            int p_r = mid + 1;
            int k;

            for (k = i; k <= j; k++) {
                if (p_l == mid + 1) {
                    aux[k] = arr[p_r];
                    p_r++;
                } else if (p_r == j + 1) {
                    aux[k] = arr[p_l];
                    p_l++;
                } else if (abs(arr[p_l]) < abs(arr[p_r])) {
                    aux[k] = arr[p_l];
                    p_l++;
                } else {
                    aux[k] = arr[p_r];
                    p_r++;
                }
            }
            for (k = i; k <= j; k++)
                arr[k] = aux[k];
        }
    }
}

int main() {
    int n, i;

    scanf("%d", &n);
    int arr[n], aux[n];
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    merge_sort(0, n - 1, arr, aux);

    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}
