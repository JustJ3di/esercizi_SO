#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

typedef int Elem;

typedef struct Stack
{
    
    Elem *dati;
    int dim;
    
    int count;
    int testa;
    int coda;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;


}Stack;

void StackInit(Stack *s,int dim);

void StackRemove(Stack *s);

void StackPush(Stack *s,Elem e);

Elem StackPop(Stack *s);

int StackSize(Stack *s);

void *Pusher(void *);
void *Popper(void *);


#endif
