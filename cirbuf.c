#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue {
    int* buf;
    int count;
    int lenbuf;
    int start;
};

struct queue Queue;

int* newb;

int DEQ(){
    int ans=Queue.buf[Queue.start];
    Queue.start=(Queue.start+1)%Queue.lenbuf;
    Queue.count--;
    return ans;
}

void ENQ(int x){

    if(Queue.count==Queue.lenbuf){
        newb= calloc(Queue.lenbuf*2 , sizeof (int));
        for(int i=0;i<Queue.count;i++){
            newb[i]=Queue.buf[(Queue.start+i)%Queue.lenbuf];
        }
        Queue.lenbuf*=2;
        Queue.start=0;
        free(Queue.buf);
        Queue.buf=newb;
    }
    Queue.count++;
    Queue.buf[(Queue.start+Queue.count-1)%Queue.lenbuf]=x;
}

int EMPTY(){
    return Queue.count==0;
}

int equel(char* a, char* b){return strcmp(a,b)==0;}

int main() {
    Queue.buf= calloc(4,sizeof (int));
    Queue.count=0;
    Queue.lenbuf=4;
    Queue.start=0;
    char command[10];
    scanf("%s",command);
    while (!equel(command, "END")){
        if(equel(command,"EMPTY")){

            if(EMPTY()) printf("true\n");
            else printf("false\n");
        }
        if(equel(command, "ENQ")) {
            int x;
            scanf("%d",&x);
            ENQ(x);
        }
        if(equel(command,"DEQ")){
            printf("%d\n",DEQ());
        }
        scanf("%s", command);
    }
    free(Queue.buf);
    return 0;
}