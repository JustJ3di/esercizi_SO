#ifndef HEADER_H
#define HEADER_H

#include "monitor.h"
#include<sys/types.h>

#define CV_PROD 0
#define CV_CONS 1

typedef struct
{
    unsigned int posizione;
    pid_t processo;
}richiesta;


typedef struct{

    richiesta vett[10];

    int testa;
    int coda;
    int count;

    Monitor M;



}Vettore_richieste;

void utente(Vettore_richieste *p,richiesta  elemento);

richiesta schedulatore(Vettore_richieste *p);


#endif 