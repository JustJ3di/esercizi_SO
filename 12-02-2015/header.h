#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

typedef struct{

    int operandi[4];
    int totale_operandi;

}buffer;

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

#define DIM  5

typedef struct header
{
    buffer elaborazioni[5];

    int stato[5];

    int liberi;
    int occupati;       
 
    pthread_mutex_t mutex;
    pthread_cond_t cv_produttori;
    pthread_cond_t cv_consumatori;

}Monitorelaborazioni;

void init_monitor(Monitorelaborazioni *);
void remove_monitor(Monitorelaborazioni *);

void Produci(Monitorelaborazioni *);
void Consuma(Monitorelaborazioni *);

#endif