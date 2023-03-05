#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define SIZE 1000000
#define True 1

typedef struct Stack {
    int cap;
    long long* Stack;
} stack;

void push(stack* st, long long value){
    (st->cap)++;

    st->Stack[(st->cap - 1)] = value;
}

void pop(stack* st){
    (st->cap)--;

}

int main() {
    stack st;
    st.cap = 0;
    st.Stack = calloc(SIZE, sizeof(long long));
    while(True){
        char operation[5];
        scanf("%s", operation);
        if (strcmp(operation, "CONST") == 0){
            long long val;
            scanf("%lli", &val);
            push(&st, val);

        }
        else if (strcmp(operation, "ADD") == 0){
            long long temp = st.Stack[(st.cap - 1)] + st.Stack[(st.cap - 2)];
            pop(&st);
            pop(&st);
            push(&st, temp);
        }
        else if (strcmp(operation, "SUB") == 0){
            long long temp = st.Stack[(st.cap - 1)] - st.Stack[(st.cap - 2)];
            pop(&st);
            pop(&st);
            push(&st, temp);
        }
        else if (strcmp(operation, "MUL") == 0){
            long long temp = st.Stack[(st.cap - 1)] * st.Stack[(st.cap - 2)];
            pop(&st);
            pop(&st);
            push(&st, temp);
        }
        else if (strcmp(operation, "DIV") == 0){
            long long temp = st.Stack[(st.cap - 1)] / st.Stack[(st.cap - 2)];
            pop(&st);
            pop(&st);
            push(&st, temp);
        }
        else if (strcmp(operation, "fmax") == 0){
            long long temp = max(st.Stack[(st.cap - 1)], st.Stack[(st.cap - 2)]);
            pop(&st);
            pop(&st);
            push(&st, temp);
        }
        else if (strcmp(operation, "MIN") == 0){
            long long temp = min(st.Stack[(st.cap - 1)], st.Stack[(st.cap - 2)]);
            pop(&st);
            pop(&st);
            push(&st, temp);
        }
        else if (strcmp(operation, "NEG") == 0){
            long long temp = -st.Stack[(st.cap - 1)];
            pop(&st);
            push(&st, temp);
        }
        else if (strcmp(operation, "DUP") == 0){
            long long temp = st.Stack[(st.cap - 1)];
            push(&st, temp);
        }
        else if (strcmp(operation, "SWAP") == 0){
            long long temp1 = st.Stack[(st.cap - 1)];
            long long temp2 = st.Stack[(st.cap - 2)];
            pop(&st);
            pop(&st);
            push(&st, temp1);
            push(&st, temp2);
        }
        else break;

    }

    printf("%lli", st.Stack[(st.cap - 1)]);
    free(st.Stack);
    return 0;
};

