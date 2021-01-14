#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>


typedef struct header
{

    int n_lettori;
    int n_scrittori;
    int wait_scrittori;  // condizione scrittore
    int wait_lettori;       //condizione lettore

    int buff;  //valore da leggere

    pthread_mutex_t mutex;

    pthread_cond_t lettori_cv;
    pthread_cond_t scrittori_cv;

}lett_scritt_t;

void *lettore(void *);

void *scrittore(void*);

void inizio_scrittura(lett_scritt_t *);

void fine_scrittura(lett_scritt_t *);

void inizio_lettura(lett_scritt_t *);
void fine_lettura(lett_scritt_t *);


#endif