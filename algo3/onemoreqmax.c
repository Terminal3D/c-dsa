#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) a > b ? a : b
#define INT_MIN (-2147483648)

typedef struct pair {
    int value;
    int max;
} pair;

struct Node {
    pair data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

struct queue {
    struct Stack enq;
    struct Stack deq;
};



struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data.value = data;
    newNode->data.max = INT_MIN;
    newNode->next = NULL;
    return newNode;
}


void push(struct Stack* stack, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}


pair pop(struct Stack* stack) {
    struct Node* temp = stack->top;
    pair data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}


pair peek(struct Stack* stack) {
    return stack->top->data;
}

int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}



void Enqueue(int value, struct queue* q) {
    if (isEmpty(&q->enq)) {
        push(&q->enq, value);
        q->enq.top->data.max = value;
    }
    else {
        int temp = peek(&q->enq).max;
        push(&q->enq, value);
        q->enq.top->data.max = MAX(value, temp);
    }
}

int Dequeue(struct queue* q) {
    if (isEmpty(&q->deq)) {
        push(&q->deq, pop(&q->enq).value);
        q->deq.top->data.max = q->deq.top->data.value;
        while (!isEmpty(&q->enq)) {
            pair item = pop(&q->enq);
            item.max = MAX(item.value, peek(&q->deq).max);
            push(&q->deq, item.value);
            q->deq.top->data.max = item.max;
        }
    }
    return pop(&q->deq).value;
}

int Maximum(struct queue* q) {
    int max_enq = INT_MIN, max_deq = INT_MIN;
    if (!isEmpty(&q->enq))
        max_enq = q->enq.top->data.max;
    if (!isEmpty(&q->deq))
        max_deq = q->deq.top->data.max;
    return MAX(max_enq, max_deq);
}


int main() {
    struct queue q;
    q.enq.top = NULL;
    q.deq.top = NULL;
    while (1) {
        char op[6];
        scanf("%s", op);
        if (!strcmp(op, "ENQ")){
            int temp;
            scanf("%i", &temp);
            Enqueue(temp, &q);
        }
        else if (!strcmp(op, "DEQ")){
            printf("%i\n", Dequeue(&q));
        }
        else if (!strcmp(op, "EMPTY")){
            if (isEmpty(&q.enq) && isEmpty(&q.deq))
                printf("true\n");
            else
                printf("false\n");
        }
        else if (!strcmp(op, "MAX")){
            printf("%i\n", Maximum(&q));
        }
        else if (!strcmp(op, "END")){
            break;
        }
    }

    while (!isEmpty(&q.enq))
        pop(&q.enq);

    while (!isEmpty(&q.deq))
        pop(&q.deq);

    return 0;
}
