#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int low, high;
} Task;

typedef struct {
    Task *data;
    int maxLength;
    int head;
} TStack;

TStack initStack(int length) {
    TStack stack;

    stack.data = (Task *)malloc(length * sizeof(Task));
    stack.maxLength = length;
    stack.head = 0;

    return stack;
}

int isStackEmpty(TStack stack) {
    return stack.head == 0;
}

void push(TStack *stack, Task x) {
    stack->data[stack->head] = x;
    stack->head++;
}

Task pop(TStack *s) {
    s->head--;
    return s->data[s->head];
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partitionSort(int startIndex, int finishIndex, int *array) {
    int index;
    for (int i = startIndex, j = startIndex; j < finishIndex; j++) {
        if (array[j] < array[finishIndex]) {
            swap(&array[i], &array[j]);
            i++;
        }

        index = i;
    }
    swap(&array[index], &array[finishIndex]);
    return index;
}

void quickSort(int arrayLength, int *array) {
    TStack stack = initStack(arrayLength);

    Task startTask;
    startTask.low = 0;
    startTask.high = arrayLength - 1;

    push(&stack, startTask);

    while (!isStackEmpty(stack)) {
        Task task = pop(&stack);

        if (task.low < task.high) {
            int maxIndex = partitionSort(task.low, task.high, array);

            Task taskFirst;
            taskFirst.low = task.low;
            taskFirst.high = maxIndex - 1;

            Task taskSecond;
            taskSecond.low = maxIndex + 1;
            taskSecond.high = task.high;

            push(&stack, taskFirst);
            push(&stack, taskSecond);
        }
    }

    free(stack.data);
}

int* inputArrayData(int arrayLength) {
    int* array = (int*)malloc(arrayLength * sizeof(int));
    if (!array) {
        return NULL;
    }
    for (int i = 0; i < arrayLength; i++) {
        scanf("%d", array + i);
    }

    return array;
}

int inputArrayLength() {
    int arrayLength;
    scanf("%d", &arrayLength);

    return arrayLength;
}

void displayArrayData(int* array, int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
}

int main() {
    int arrayLength = inputArrayLength();
    int* array = inputArrayData(arrayLength);
    quickSort(arrayLength, array);
    displayArrayData(array, arrayLength);
    free(array);
    return 0;
}
