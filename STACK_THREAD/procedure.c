#include"header.h"
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>


void StackInit(Stack *s,int dim){


    s->dati = (Elem *)malloc(sizeof(Elem)*dim);


    pthread_mutex_init(&(s->mutex),NULL);
    pthread_cond_init(&(s->cv_cons),NULL);
    pthread_cond_init(&(s->cv_prod),NULL);

    s->testa = 0;

    s->dim = dim;

    printf("STACK INIZIALIZZATO di dimensione <%d> \n",s->dim);

}


void StackRemove(Stack *s){

    free(s->dati);

    pthread_mutex_destroy(&(s->mutex));
    pthread_cond_destroy(&(s->cv_cons));
    pthread_cond_destroy(&(s->cv_prod));


}

void StackPush(Stack *s,Elem e){


    pthread_mutex_lock(&(s->mutex));


    while (s->testa == s->dim)
    {
        pthread_cond_wait(&(s->cv_prod),&(s->mutex));
    }
    

    s->dati[s->testa] = e;

    s->testa++;

    pthread_cond_signal(&(s->cv_cons));

    pthread_mutex_unlock(&(s->mutex));


}


Elem StackPop(Stack *s){

    int elemento;

    pthread_mutex_lock(&(s->mutex));

    while (s->testa  == 0)
    {
        pthread_cond_wait(&(s->cv_cons),&(s->mutex));
    }
    

   elemento = s->dati[s->testa];
    
    s->testa--;

    pthread_cond_signal(&(s->cv_prod));
    pthread_mutex_unlock(&(s->mutex));

    return elemento;

}


int StackSize(Stack *s){

    pthread_mutex_lock(&s->mutex);

    int dim = s->testa;

    pthread_mutex_unlock(&s->mutex);
    return dim;

}



void *Pusher(void *b){

    Stack *s = (Stack *)b;

    for (size_t i = 0; i < 4; i++)
    {
        Elem e = rand()%11;
        printf("pusho valore %d   \n",e);
        StackPush(s,e);
        sleep(1);
    }
    
    

    pthread_exit(NULL);
}

void *Popper(void *b){

    Stack *s = (Stack *)b;

    for (size_t i = 0; i < 10; i++)
    {
        int x,y;
        x = StackPop(s);
        printf("pop del valore PRIMO     %d\n",x);

        y = StackPop(s);
        printf("pop del valore SECONDO   %d \n",y);

        printf("La loro somma <%d>\n",(x+y));
        sleep(3);

    }
    
    pthread_exit(NULL);
}