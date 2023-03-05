#include <stdio.h>
#include <stdlib.h>

struct Task {
    int low, high;
};

typedef struct stack_task {
    int cap;
    struct Task tasks[1000000];
} stack;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void push(stack* t_stack, struct Task task) {
    t_stack->tasks[++t_stack->cap] = task;
}

struct Task pop(stack* t_stack) {
    return t_stack->tasks[t_stack->cap--];
}

void qsort_stack(int* array, int n) {
    stack t_stack;
    t_stack.cap = -1;
    struct Task task = {0, n - 1};
    push(&t_stack, task);
    while (t_stack.cap != -1) {
        struct Task temp = pop(&t_stack);
        int pivot = partition(array, temp.low, temp.high);
        if (pivot - 1 > temp.low) {
            struct Task left = {temp.low, pivot - 1};
            push(&t_stack, left);
        }
        if (pivot + 1 < temp.high) {
            struct Task right = {pivot + 1, temp.high};
            push(&t_stack, right);
        }
    }
}

int main() {
    int n;
    scanf("%i", &n);
    int* array = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%i", &array[i]);
    qsort_stack(array, n);
    for (int i = 0; i < n; i++)
        printf("%i ", array[i]);
    free(array);
    return 0;
}
