#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#include<pthread.h>
#include"header.h"

void *Produttore(void *ps){

    Prod_cons_t *pc = (Prod_cons_t*)ps;

    srand(time(NULL));

    int msg = rand()%20;

    printf("IO PRODUCO... il valore ...%d\n",msg);


    Produzione(pc,msg);

    pthread_exit(NULL);
}

void *Consumatore(void *ps){

    Prod_cons_t *pc =(Prod_cons_t*)ps;

    Consumazione(pc);

    pthread_exit(NULL);


}


void Produzione(Prod_cons_t *pc,int msg){

    pthread_mutex_lock(&pc->mutex);

    while(pc->count == DIM){
        pthread_cond_wait(&pc->cv_produttore,&pc->mutex);
    }

    pc->buff[pc->procuco_in_testa]  = msg;

    pc->procuco_in_testa = (pc->procuco_in_testa+1)%DIM;

    pc->count++;

    pthread_cond_signal(&pc->cv_consumatore);


    pthread_mutex_unlock(&pc->mutex);


}

void Consumazione(Prod_cons_t *pc){

    pthread_mutex_lock(&pc->mutex);

    while(pc->count == 0){
        pthread_cond_wait(&pc->cv_consumatore,&pc->mutex);
    }

    printf("consumer.................. %d\n",pc->buff[pc->consumo_in_coda]);

    pc->consumo_in_coda = (pc->consumo_in_coda+1)%DIM;

    pc->count--;

    pthread_cond_signal(&pc->cv_produttore);

    pthread_mutex_unlock(&pc->mutex);
    
}