#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

typedef struct{
    int indirizzo;
    int dato;
}Buffer;

typedef struct{

    Buffer vettore[10];

    int coda;
    int testa;
    int count;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;

}GestioneIO;


void Inizializza(GestioneIO *g);
void Produci(GestioneIO *g,Buffer *b);
int Consuma(GestioneIO *g,Buffer *b);
void Rimuovi(GestioneIO *g);

#endif