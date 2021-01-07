#include "prodcons.h"
#include "semafori.h"

void produttore(prodcons_t *ps,int id_sem){

    sem_wait(id_sem,SPA_DISP);

    sem_wait(id_sem,MUTEX_P);

    ps->buffer[ps->testa] = rand()%100;
    printf("valore prodotto %d\n",ps->buffer[ps->testa]);
    
    ps->testa = ((ps->testa)+1)%DIM;  //AUMENTO IN MODULO

    sem_signal(id_sem,MUTEX_P);

    sem_signal(id_sem,MSG_DISP);

}

void consumatore(prodcons_t *ps,int id_sem){


    sem_wait(id_sem,MSG_DISP);

    sem_wait(id_sem,MUTEX_C);

    printf("valore consumato %d \n",ps->buffer[ps->coda]);  

    ps->coda = ((ps->coda)+1)%DIM;

    sem_signal(id_sem,MUTEX_C);

    sem_signal(id_sem,SPA_DISP);


}
