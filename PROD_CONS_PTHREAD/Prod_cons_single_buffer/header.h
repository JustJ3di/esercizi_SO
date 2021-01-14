#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>


#define NUM_THREADS 10

typedef struct prod_cons {

    int buff;

    int prod_ok;       //condizioni di produzione consumazione
    int cons_ok;

    pthread_mutex_t mutex;  //mutex per l'accesso al monitor

    pthread_cond_t mex_disp;  //varibili condition
    pthread_cond_t spa_disp; //

}prod_cons_t;


void *Produco(void*);

void *Consumo(void*);

void Produttore(prod_cons_t *,int);

void Consumatore(prod_cons_t *);

#endif