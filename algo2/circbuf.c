#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buf{
    int *array;
    int start;
    int end;
    int len;
    int count;
};

void clear(struct buf *Buf){
    free(Buf->array);
    free(Buf);
}

int next_ind(int ind, int len){
    return (ind + 1) % len;
}

struct buf *new_buf(struct buf *Buf){
    struct buf *newB = malloc(sizeof(struct buf));
    newB->array = malloc(Buf->len * 2 * sizeof(int));
    newB->start = 0;
    newB->end = 0;
    newB->len = 2 * Buf->len;
    while(Buf->start != Buf->end){
        newB->array[newB->end++] = Buf->array[Buf->start];
        Buf->start = next_ind(Buf->start, Buf->len);
    }
    newB->count = newB->end;
    free(Buf->array);
    free(Buf);
    return newB;
}

int main() {
    struct buf *Buf = malloc(sizeof(struct buf));
    Buf->end = 0;
    Buf->len = 4;
    Buf->start = 0;
    Buf->count = 0;
    Buf->array = malloc(4 * sizeof(int));
    char instruction[100];
    while(1){
        scanf("%s", instruction);
        if(strcmp(instruction, "END") == 0){
            clear(Buf);
            return 0;
        }
        if(strcmp(instruction, "ENQ") == 0){
            int val;
            scanf("%d", &val);
            Buf->array[Buf->end] = val;
            Buf->count++;
            Buf->end = next_ind(Buf->end, Buf->len);
            if(Buf->len == Buf->count){
                Buf = new_buf(Buf);
            }
        }
        if(strcmp(instruction, "DEQ") == 0){
            printf("%d\n", Buf->array[Buf->start]);
            Buf->start = next_ind(Buf->start, Buf->len);
        }
        if(strcmp(instruction, "EMPTY") == 0){
            if(Buf->count == 0)
                printf("true\n");
            else
                printf("false\n");
        }
    }
    return 0;
}