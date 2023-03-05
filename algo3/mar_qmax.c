#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX(a, b) a > b ? a : b

typedef struct element {
    long long item;
    long long max;
} element;

typedef struct Queue {
    element* data;
    long long top1;
    long long top2;
} Queue;

Queue InitQueue() {
    Queue queue;
    queue.data = malloc(1000000 * sizeof(element));
    queue.data[500000].item = 0;
    queue.data[500000].max = 0;
    queue.top1 = -1;
    queue.top2 = 500000;
    return queue;
}

void Push1(element Item, Queue* q) {
    q->data[(++q->top1)] = Item;
}

void Push2(element Item, Queue* q) {
    q->data[(++q->top2)] = Item;
}

element Pop1(Queue* q) {
    return q->data[(q->top1--)];
}

element Pop2(Queue* q) {
    return q->data[(q->top2--)];
}

int isEmpty1(Queue* q) {
    return q->top1 == -1;
}

int isEmpty2(Queue* q) {
    return q->top2 == 500000;
}

element getTop1(Queue* q) {
    return q->data[q->top1];
}

element getTop2(Queue* q) {
    return q->data[q->top2];
}

void isEmpty(Queue* q) {
    if (isEmpty1(q) && isEmpty2(q))
        printf("true\n");
    else
        printf("false\n");
}

void Enqueue(long long num, Queue* q) {
    element new_elem;
    new_elem.item = num;
    if (isEmpty1(q))
        new_elem.max = num;
    else
        new_elem.max = MAX(num, getTop1(q).max);
    Push1(new_elem, q);
}

void Dequeue(Queue* q) {

    if (isEmpty2(q)){
        element temp = Pop1(q);
        temp.max = temp.item;
        Push2(temp, q);
        while (!isEmpty1(q)) {
           temp = Pop1(q);
           temp.max = MAX(temp.item, getTop2(q).max);
           Push2(temp, q);
        }
    }
    printf("%lli\n", Pop2(q).item);
}

void Maximum(Queue* q) {
    if (isEmpty1(q) && isEmpty2(q))
        printf("Empty\n");

    else if (isEmpty1(q))
        printf("%lli\n", getTop2(q).max);

    else if (isEmpty2(q))
        printf("%lli\n", getTop1(q).max);

    else
        printf("%lli\n", MAX(getTop2(q).max, getTop1(q).max));


}


int main() {
    Queue q = InitQueue();
    while (1) {
        char op[6];
        scanf("%s", op);
        if (!strcmp(op, "ENQ")) {
            long long value;
            scanf("%lli", &value);
            Enqueue(value, &q);
        }
        else if (!strcmp(op, "DEQ")) {
            Dequeue(&q);
        }
        else if (!strcmp(op, "EMPTY")) {
            isEmpty(&q);
        }
        else if (!strcmp(op, "MAX")) {
            Maximum(&q);
        }
        else if (!strcmp(op, "END")) {
            break;
        }

    }
    free(q.data);
    return 0;
}