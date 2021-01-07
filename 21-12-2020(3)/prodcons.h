#ifndef _HEADER_H_
#define _HEADER_H_

#include "monitor_hoare.h"

#include <sys/types.h>

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

#define PATH1 "."

typedef struct {

    int stato;      // LIBERO, OCCUPATO, IN_USO
    pid_t produttore;
    size_t dimensione;
    key_t chiave;

} Buffer;

#define DIM 4

typedef struct {

    Buffer vettore[DIM];
    /* TBD: Completare la struttura dati monitor */
    int coda ;
    int count ;
    int testa ;

    Monitor M;


} MonitorStreaming;

#define CV_PROD 0
#define CV_CONS 1

void inizializza(MonitorStreaming * p);
void produci(MonitorStreaming * p, char * stringa, size_t lunghezza, key_t chiave);
void consuma(MonitorStreaming * p, char * stringa, size_t * lunghezza);
void distruggi(MonitorStreaming * p);


#endif