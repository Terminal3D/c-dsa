#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 1000000
#define True 1



typedef struct {
    int value;
    int max_value;
} item;

typedef struct {
    item arr[SIZE];
    int top1;
    int top2;
} DoubleStack;

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int isEmpty1(DoubleStack *stack) {
    return stack->top1 == -1;
}

int isEmpty2(DoubleStack *stack) {
    return stack->top2 == SIZE;
}

void push1(DoubleStack *stack, item value) {
    if (stack->top1 > stack->top2) {
        printf("Stack Overflow");
        exit(-1);
    }
    stack->arr[(++stack->top1)] = value;
}

void push2(DoubleStack *stack, item value) {
    if (stack->top1 > stack->top2) {
        printf("Stack Overflow");
        exit(-1);
    }
    stack->arr[(--stack->top2)] = value;
}

item pop1(DoubleStack *stack){
    if (isEmpty1(stack)) {
        printf("Stack is Empty");
        exit(-1);
    }
    return stack->arr[(stack->top1--)];
}

item pop2(DoubleStack *stack){
    if (isEmpty2(stack)) {
        printf("Stack is Empty");
        exit(-1);
    }
    return stack->arr[(stack->top2++)];
}

void InitQueue(DoubleStack* queue) {
    queue->top1 = -1;
    queue->top2 = SIZE;
}

void Enqueue(DoubleStack* stack, item item) {
    if (isEmpty1(stack)) {
        item.max_value = item.value;
        push1(stack, item);
    }
    else {
        item.max_value = max(item.value, stack->arr[stack->top1].max_value);
        push1(stack, item);
    }
}

int Dequeue(DoubleStack* stack) {
    if (isEmpty2(stack)) {
        int temp_max = INT_MIN;
        int temp;
        while(!isEmpty1(stack)) {
            item item;
            item.value = pop1(stack).value;
            temp = max(item.value, temp_max);
            item.max_value = temp;
            temp_max = temp;
            push2(stack, item);
        }
    }
    return pop2(stack).value;
}

int Maximum(DoubleStack* stack) {
    if (!isEmpty1(stack) && !isEmpty2(stack))
        return (max(stack->arr[stack->top1].max_value, stack->arr[stack->top2].max_value));
    else if (!isEmpty1(stack))
        return stack->arr[stack->top1].max_value;
    else if (!isEmpty2(stack))
        return stack->arr[stack->top2].max_value;
    else {
        printf("Can't get maximum of an empty queue");
        exit(-1);
    }
}

int QueueEmpty(DoubleStack* stack) {
    return (isEmpty1(stack) && isEmpty2(stack));
}

int main() {
    DoubleStack queue;
    InitQueue(&queue);
    char op[6];
    while (True) {
        scanf("%s", op);
        if (op[0] == 'E' && op[1] == 'N' && op[2] == 'Q') {
            item temp;
            scanf("%i", &temp.value);
            Enqueue(&queue, temp);
        }
        else if (op[0] == 'D')
            printf("%i\n",Dequeue(&queue));
        else if (op[0] == 'E' && op[1] == 'M') {
            if (QueueEmpty(&queue))
                printf("true\n");
            else
                printf("false\n");
        }
        else if (op[0] == 'M')
            printf("%i\n", Maximum(&queue));
        else
            break;
    }
    return 0;
}