#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

#define DIM 10

typedef struct header{

    int procuco_in_testa;   //indice_testa
    int consumo_in_coda;    //indice_coda
 
    int count;

    int buff[DIM];


    pthread_mutex_t mutex;

    pthread_cond_t cv_produttore;

    pthread_cond_t cv_consumatore;




}Prod_cons_t;


void *Produttore(void *);  //Produttore

void *Consumatore(void *);  //consumatore

void Produzione(Prod_cons_t*,int);

void Consumazione(Prod_cons_t*);


#endif