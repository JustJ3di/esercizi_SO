#include"header.h"
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>



int main(){

    pthread_t thread[6];



    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    Stack *s = (Stack *)malloc(sizeof(Stack));

    StackInit(s,5);

    srand(time(NULL));

    for (size_t i = 0; i < 6; i++)
    {
       
        pthread_create(&thread[i],&attr,Pusher,(void *)s);
     
    }
        pthread_create(&thread[5],&attr,Popper,(void *)s);

    for (size_t i = 0; i < 6; i++)
    {
        pthread_join(thread[i],NULL);
    }
    
    pthread_attr_destroy(&(attr));
    StackRemove(s);
    free(s);

    return 0;
}