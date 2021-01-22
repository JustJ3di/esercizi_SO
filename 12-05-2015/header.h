#ifndef HEADER_H

#define HEADER_H

#include<pthread.h>


typedef struct{

    int identificativo;
    int quota;

}volo;

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

typedef struct{

    volo vettori_voli[3];
    int vett_stato[3];

    int occupati;
    int liberi;
    int id;

    pthread_cond_t cv_consumatori;
    pthread_cond_t cv_produttori;
    pthread_mutex_t mutex;

}gestionevoli;


void inseriscivolo(gestionevoli *g,int identificativo);
void rimuovivolo(gestionevoli *g,int identificativo);
void aggiornavolo(gestionevoli *g,int identificativo,int quota);



#endif
