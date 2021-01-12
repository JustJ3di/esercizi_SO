#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

#define SIZE 10

typedef struct 
{
    int indirizzo;
    int dato;

}Buffer;

typedef struct
{

    Buffer vettore[10];

    int head;
    int tail;

    int count;    

    pthread_cond_t cv_produttore;

    pthread_mutex_t mutex;


}GestioneIO;

/*thread_function*/

void *Produttore(void *);
void *Consumatore(void *);


void Inizializza(GestioneIO *);
void Produci(GestioneIO *,Buffer *);
int Consuma(GestioneIO *,Buffer *);


#endif
