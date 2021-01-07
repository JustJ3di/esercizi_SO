#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>

#define DIM 6

typedef int Frame[2][2];

typedef struct {

    Frame vettore[DIM];

    /* TBD: Completare la struttura dati monitor */

    int count;
    int coda;
    int testa;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;

} MonitorStreaming;

void inizializza(MonitorStreaming * m);
void produci(MonitorStreaming * m, Frame f);
void consuma(MonitorStreaming * m, Frame f);
void bufferizza(MonitorStreaming * m, int n);
void distruggi(MonitorStreaming * m);

#endif
