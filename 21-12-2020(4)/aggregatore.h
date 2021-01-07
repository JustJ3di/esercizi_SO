#ifndef _AGGREGATORE_H_
#define _AGGREGATORE_H_

#include <pthread.h>

typedef struct {

    int variabile;

    /* TBD: Completare la struttura dati monitor */

    int num_scritt;
    int num_lett;
    int wait_lett;
    int wait_scritt;

    int index;

    int coda_sensore;
    int code_collettori[3];

    pthread_mutex_t mutex;
    pthread_cond_t cv_lett;
    pthread_cond_t cv_scritt;
    pthread_mutex_t mutex_l;

} MonitorLS;

void aggregatore(int id_coda_sensore, int id_code_collettori[3]);
void * thread_lettore_1(void *);
void * thread_lettore_2(void *);
void * thread_lettore_3(void *);
void * thread_scrittore(void *);
void lettura(MonitorLS *, int * valore);
void scrittura(MonitorLS *, int valore);

#endif