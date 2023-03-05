#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define SIZE 1000000
#define True 1
#define MAX(a, b) a > b ? a : b

typedef struct elem {
    long long num;
    long long cur_max;
} el;

typedef struct Stack {
    long long top;
    el* data;
} stack;

typedef struct Queue {
    stack enq_stack;
    stack deq_stack;
} queue;

void InitStack(stack* s) {
    s->top = -1;
    s->data = malloc(SIZE * sizeof(el));
}

void Push(stack* s, el value) {
    s->top++;
    s->data[s->top] = value;
}

el Pop(stack* s) {
    el value = s->data[s->top];
    s->top--;
    return value;
}

int StackEmpty(stack* s) {
    return (s->top == -1);
}

el StackTop(stack* s) {
    return s->data[s->top];
}

void InitQueue(queue* q) {
    InitStack(&q->enq_stack);
    InitStack(&q->deq_stack);
}

void Enqueue(queue* q, long long value) {
    el temp;
    temp.num = value;
    if (StackEmpty(&q->enq_stack))
        temp.cur_max = value;
    else
        temp.cur_max = fmax(value, StackTop(&q->enq_stack).cur_max);

    Push(&q->enq_stack, temp);
}

long long Dequeue(queue* q) {
    if (StackEmpty(&q->deq_stack)) {
        while (!StackEmpty(&q->enq_stack)) {
            el tmp = Pop(&q->enq_stack);
            if (StackEmpty(&q->deq_stack))
                tmp.cur_max = tmp.num;
            else if (!StackEmpty(&q->deq_stack))
                tmp.cur_max = fmax(tmp.num, StackTop(&q->deq_stack).cur_max);
            Push(&q->deq_stack, tmp);
        }
    }
    return Pop(&q->deq_stack).num;
}

int QueueEmpty(queue* q) {
    return (StackEmpty(&q->enq_stack) && StackEmpty(&q->deq_stack));
}

long long Maximum(queue* q) {
    long long max_value_enq = LLONG_MIN;
    long long max_value_deq = LLONG_MIN;

    if (!StackEmpty(&q->enq_stack)) {
        max_value_enq = StackTop(&q->enq_stack).cur_max;
    }

    if (!StackEmpty(&q->deq_stack)) {
        max_value_deq = StackTop(&q->deq_stack).cur_max;
    }

    long long max_value = MAX(max_value_deq, max_value_enq);

    return max_value;
}

int main() {
    queue q;
    InitQueue(&q);
    while (True){
        char operation[6];
        scanf("%s", operation);
        if (strcmp(operation, "ENQ") == 0){
            long long temp;
            scanf("%lli", &temp);
            Enqueue(&q, temp);
        }
        else if (strcmp(operation, "DEQ") == 0){
            printf("%lli\n", Dequeue(&q));
        }
        else if (strcmp(operation, "EMPTY") == 0){
            if (QueueEmpty(&q))
                printf("true\n");
            else
                printf("false\n");
        }
        else if (strcmp(operation, "fmax") == 0){
            printf("%lli\n", Maximum(&q));
        }
        else break;
    }
    free(q.enq_stack.data);
    free(q.deq_stack.data);
    return 0;
}