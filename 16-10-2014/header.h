#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

typedef struct{int a;int b;}elemento;

#define DIM 5

typedef struct 
{

    elemento vettore[5];

    int count;
    int coda;
    int testa;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;


}MonitorVettore;


typedef struct
{

    elemento buffer;

    int num_lettori;
    int num_scrittori;
    int wait_lettori;
    int wait_scrittori;

    pthread_cond_t cv_scritt;
    pthread_cond_t cv_lett;
    pthread_mutex_t mutex;

}MonitorBuffer;

typedef struct
{


    MonitorBuffer mb;
    MonitorVettore mv;

}Monitor;


void genera(MonitorVettore *v,elemento e);
elemento preleva(MonitorVettore *v);
void aggiorna(MonitorBuffer *b,elemento e);
void consulta(MonitorBuffer *b);


#endif
