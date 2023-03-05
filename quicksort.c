//Имплементация на 1 балл.

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* array, int low, int high) {
    int cen = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] < cen) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

void quicksort(int* array, int low, int high, int m) {
    if (low < high) {
        if (high - low < m) {
            for (int i = low; i < high; i++) {
                for (int j = i + 1; j <= high; j++) {
                    if (array[i] > array[j]) {
                        swap(&array[i], &array[j]);
                    }
                }
            }
        } else {
            int cen_index = partition(array, low, high);
            quicksort(array, low, cen_index - 1, m);
            quicksort(array, cen_index + 1, high, m);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int* array = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    quicksort(array, 0, n - 1, m);

    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    free(array);
    return 0;
}
