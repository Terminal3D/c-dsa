#include <stdlib.h>
#include <stdio.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define True 1

typedef struct Node {
    long data;
    struct Node* next;
} node;


typedef struct Stack {
    node* top;
    int cap;
} stack;

void push(long num, stack* stack){
    node* temp = malloc(sizeof(node));
    temp->data = num;
    temp->next = stack->top;
    stack->top = temp;
    (stack->cap)++;
}

long pop(stack* stack){

    long value = stack->top->data;
    node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    (stack->cap)--;
    return value;
}

void s_const(stack* stack) {
    int num;
    scanf("%i", &num);
    push(num,stack);
}

void add(stack* stack) {
    long val1 = pop(stack);
    long val2 = pop(stack);
    push(val1 + val2, stack);
}

void sub(stack* stack) {
    long val1 = pop(stack);
    long val2 = pop(stack);
    push(val1 - val2, stack);
}

void mul(stack* stack) {
    long val1 = pop(stack);
    long val2 = pop(stack);
    push(val1 * val2, stack);
}

void s_div(stack* stack) {
    long val1 = pop(stack);
    long val2 = pop(stack);
    push(val1 / val2, stack);
}

void s_max(stack* stack) {
    long val1 = pop(stack);
    long val2 = pop(stack);
    push(MAX(val1, val2), stack);
}

void s_min(stack* stack) {
    long val1 = pop(stack);
    long val2 = pop(stack);
    push(MIN(val1, val2), stack);
}

void neg(stack* stack) {
    stack->top->data = - stack->top->data;
}

void dup(stack* stack) {
    push(stack->top->data, stack);
}

void swap(stack* stack) {
    long val1 = pop(stack);
    long val2 = pop(stack);
    push(val1, stack);
    push(val2, stack);
}

int main() {
    stack stack;
    stack.cap = 0;
    stack.top = NULL;
    char op[6];
    while(True) {
        scanf("%s", op);
        if (op[0] == 'C')
            s_const(&stack);
        else if (op[0] == 'A')
            add(&stack);
        else if (op[0] == 'S' && op[1] == 'U')
            sub(&stack);
        else if (op[0] == 'M' && op[1] == 'U')
            mul(&stack);
        else if (op[0] == 'D' && op[1] == 'I')
            s_div(&stack);
        else if (op[0] == 'M' && op[1] == 'A')
            s_max(&stack);
        else if (op[0] == 'M')
            s_min(&stack);
        else if (op[0] == 'N')
            neg(&stack);
        else if (op[0] == 'D')
            dup(&stack);
        else if (op[0] == 'S')
            swap(&stack);
        else
            break;
    }
    printf("%li", stack.top->data);
    while (stack.top != NULL)
        pop(&stack);
}