#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

typedef struct {int a; int b;}elemento;

typedef struct 
{
    elemento vettore[5];

    int head;
    int tail;
    int count;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;

}MonitorVettore;


typedef struct{

    elemento buffer;

    int num_lett;
    int num_scrit;
    int wait_scrit;
    int wait_lett;

    pthread_mutex_t mutex;
    pthread_cond_t cv_lett;
    pthread_cond_t cv_scrit;


}MonitorBuffer;

typedef struct{

    MonitorBuffer b;
    MonitorVettore v;

}Monitor;


void *Generatore(void *);
void *Aggiornatore(void *);
void *Destinatario(void *);

void init_monitor(MonitorBuffer *,MonitorVettore *);
void remove_monitor(MonitorBuffer *,MonitorVettore *);

void genera(MonitorVettore *,elemento );
elemento preleva(MonitorVettore *);
void aggiorna(MonitorBuffer *,elemento );
void consulta(MonitorBuffer *);


#endif