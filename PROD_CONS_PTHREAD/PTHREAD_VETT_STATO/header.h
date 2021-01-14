#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2   //definisco gli stati del vettore: stato[]

#define DIM_BUFF 10


typedef struct prod_cons{

    pthread_mutex_t mutex;

    pthread_cond_t prod_cv;
    pthread_cond_t cons_cv;

    int buff[10];
    int stato[10];
    int numero_liberi;  //indice del buffer;
    int num_occupati;

}prod_cons_t;

//funzione lanciate dai thread

void *Produttore(void *);   
void *Consumatore(void *);

//funzione che volgono l'effettiva produzione e consumazione del messaggio

void Produco(prod_cons_t *);

//la funzione consumo mi ritorna il valore del buffer[ ] che è oviamente un intero
int Consumo(prod_cons_t *);




#endif