#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) a > b ? a : b

typedef struct {
    int low, high;
} Task;

int partition(int *array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;
    return i + 1;
}

void quicksort(int *array, int n) {
    Task stack[n];
    int top = -1;
    stack[++top] = (Task){0, n - 1};

    while (top >= 0) {
        Task task = stack[top--];
        int low = task.low;
        int high = task.high;
        int p = partition(array, low, high);
        if (p - 1 > low) {
            stack[++top] = (Task){low, p - 1};
        }
        if (p + 1 < high) {
            stack[++top] = (Task){p + 1, high};
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    quicksort(array, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}
