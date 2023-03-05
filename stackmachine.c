#include <string.h>
#include <stdio.h>
#define MAX_SIZE 1000000
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))


struct Stack{
    long long stack[MAX_SIZE];
    int stack_size;
};

void stack_push(struct Stack* st, long long num){

    (st->stack_size)++;
    st->stack[st->stack_size] = num;

}

void stack_pop(struct Stack* st, long long num){

    (st->stack_size)--;
    st->stack[st->stack_size] = num;

}


int main(){
    struct Stack st;
    st.stack_size = -1;
    while (1) {
        char op[5];
        scanf("%s", op);
        if (strcmp(op, "CONST") == 0){
            long long num;
            scanf("%lli", &num);
            stack_push(&st, num);
            continue;
        }
        else if (strcmp(op, "ADD") == 0){
            long long sum = st.stack[st.stack_size] + st.stack[st.stack_size - 1];
            stack_pop(&st, sum);
            continue;
        }
        else if (strcmp(op, "SUB") == 0){
            long long sub = st.stack[st.stack_size] - st.stack[st.stack_size - 1];
            stack_pop(&st, sub);
            continue;
        }
        else if (strcmp(op, "MUL") == 0){
            long long mul = st.stack[st.stack_size] * st.stack[st.stack_size - 1];
            stack_pop(&st, mul);
            continue;
        }
        else if (strcmp(op, "DIV") == 0){
            long long div = st.stack[st.stack_size] / st.stack[st.stack_size - 1];
            stack_pop(&st, div);
            continue;
        }
        else if (strcmp(op, "MAX") == 0){
            long long maximum = max(st.stack[st.stack_size], st.stack[st.stack_size - 1]);
            stack_pop(&st, maximum);
            continue;
        }
        else if (strcmp(op, "MIN") == 0){
            long long minimum = min(st.stack[st.stack_size], st.stack[st.stack_size - 1]);
            stack_pop(&st, minimum);
            continue;
        }
        else if (strcmp(op, "NEG") == 0){
            st.stack[st.stack_size] = 0 - st.stack[st.stack_size];
            continue;
        }
        if (strcmp(op, "DUP") == 0){
            long long dup = st.stack[st.stack_size];
            stack_push(&st, dup);
            continue;
        }
        if (strcmp(op, "SWAP") == 0){
            long long temp = st.stack[st.stack_size - 1];
            stack_pop(&st, st.stack[st.stack_size]);
            stack_push(&st, temp);
        }
        else if (strcmp(op, "END") == 0){
            printf("%lli", st.stack[st.stack_size]);
            break;
        }


    }
return 0;

}