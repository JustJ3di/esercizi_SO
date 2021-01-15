#include"header.h"
#include<pthread.h>
#include<semaphore.h>

void produci(Buff *b,int val){

    sem_wait(&b->spazio_disp);
    sem_wait(&b->mutex_p);

    b->vet[b->head] = val;
    b->head = (b->head+1)%DIM;

    sem_post(&b->mutex_p);
    sem_post(&b->mex_disp);     


}

int consuma(Buff* b){

    sem_wait(&b->mex_disp);
    sem_wait(&b->mutex_c);

    int ret = b->vet[b->tail];
    b->tail = (b->tail +1)%DIM;

    sem_post(&b->mutex_c);
    sem_post(&b->spazio_disp);

    return ret;

}
