#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 1000000

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

struct Queue {
    int *data;
    int *max;
    int top_1;
    int top_2;
};

void InitQueue(struct Queue *s) {
    s->data = (int *) malloc(sizeof(int) * size);
    s->max = (int *) malloc(sizeof(int) * size);
    s->top_1 = 0;
    s->top_2 = size - 1;
}

int StackEmpty_1(struct Queue *s) {
    int x = s->top_1 == 0;
    return x;
}

int StackEmpty_2(struct Queue *s) {
    int x = s->top_2 == size - 1;
    return x;
}

void Push_1(struct Queue *s, int x) {
    if (s->top_2 < s->top_1) {
        printf("Error: Overflow\n");
        exit(1);
    }
    s->data[++(s->top_1)] = x;
}

void Push_2(struct Queue *s, int x) {
    if (s->top_2 < s->top_1) {
        printf("Error: Overflow\n");
        exit(1);
    }

    s->data[--(s->top_2)] = x;
}

int Pop_1(struct Queue *s) {
    if (StackEmpty_1(s)) {
        printf("Error: Underflow\n");
        exit(1);
    }
    int x = s->data[s->top_1];
    s->top_1--;

    return x;
}

int Pop_2(struct Queue *s) {
    if (StackEmpty_2(s)) {
        printf("Error: Underflow\n");
        exit(1);
    }
    int x = s->data[s->top_2];
    s->top_2++;
    return x;
}

void Enqueue(struct Queue *s, int x) {
    if (StackEmpty_1(s) == 1)
        s->max[s->top_1 + 1] = x;
    else
        s->max[s->top_1 + 1] = max(x, s->max[s->top_1]);
    Push_1(s, x);
}

int Dequeue(struct Queue *s) {
    if (StackEmpty_2(s) == 1) {
        int x = Pop_1(s);
        Push_2(s, x);
        s->max[s->top_2] = x;
        while (StackEmpty_1(s) != 1) {
            x = Pop_1(s);
            if (x > s->max[s->top_2])
                s->max[s->top_2 - 1] = x;
            else
                s->max[s->top_2 - 1] = s->max[s->top_2];
            Push_2(s, x);
        }
    }
    int y = Pop_2(s);
    return y;
}

int Maximum(struct Queue *s) {
    if (StackEmpty_1(s) && StackEmpty_2(s)) {
        printf("Queue is empty!");
        return 0;
    }
    else if (StackEmpty_1(s))
        return s->max[s->top_2];
    else if (StackEmpty_2(s))
        return s->max[s->top_1];
    else
        return max(s->max[s->top_2], s->max[s->top_1]);
}



int main() {
    int point = 1;
    struct Queue s;

    InitQueue(&s);
    int x;
    char operation[6];
    while (point) {
        if (scanf("%s", operation) != 1)
            break;

        if (!strcmp(operation, "ENQ")) {
            if (scanf("%i", &x) != 1)
                break;
            Enqueue(&s, x);
        }
        else if (!strcmp(operation, "DEQ"))
            printf("%i\n", Dequeue(&s));
        else if (!strcmp(operation, "EMPTY")) {
            if (StackEmpty_1(&s) && StackEmpty_2(&s)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        }
        else if (!strcmp(operation, "MAX"))
            printf("%i\n", Maximum(&s));
        else
            break;
    }

    free(s.data);
    free(s.max);

    return 0;
}