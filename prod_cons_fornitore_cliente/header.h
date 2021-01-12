#ifndef HEADER_H
#define HEADER_H

#include"monitor_signal_continue.h"

#define CV_FORNITORE 0
#define CV_CLIENTE   1

#define DIM 100


#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

typedef struct{

    unsigned int id_fornitore;
    unsigned int stato;


}scaffale;

typedef struct magazzino
{

    scaffale scaff[100];

    Monitor m;

    int livello_scorte;

    int numero_liberi;



}Magazzino_t;


void Fornitore(Magazzino_t *);

void Cliente(Magazzino_t *);


#endif
