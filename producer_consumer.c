#include <stdio.h>
#define MAX 10

int sharedMemory[MAX];
int mutex = 1;
int empty = MAX-1;
int full = 0;

void wait(int *s){
    s--;
}

void signal(int *s){
    s++;
}
void producer(int A[],int *m, int *e, int *f){
    if(*e != 0){
        wait(m);
        A[f] = 1;
        wait(e);
        signal(f);
        signal(m);
    }
}
void consumer(int A[],int *m, int *e, int *f){
    if(*f != 0){
        wait(m);
        A[f] = 1;
        signal(e);
        wait(f);
        signl(m);
    }
}
void main(){
    int optn;
    printf("buffer size is 10");
    printf("1.produce\n2.consume\n3.exit");
    while(1){
        printf("enter optn: ");
        scanf("%d", &)
        if(optn == 1){
            producer(sharedMemory, &mutex, &)
        }
    }
}
