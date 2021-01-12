#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

typedef struct monitor 
{

    int buffer;

    int num_lettori;
    int num_scrittori;
    int wait_scrittori;
    int wait_lettori;

    pthread_mutex_t mutex;
    pthread_cond_t cv_scrittore;
    pthread_cond_t cv_lettore;    
    

}BufferLS;

typedef struct 
{
    BufferLS Buff_scritt;

    BufferLS Buff_lett1;
    BufferLS Buff_lett2;

}Monitor;



void *Scrittore(void *);
void *Lettore_Scrittore(void *);
void *Lettore(void *);


void Scrittura(BufferLS *,int);
int Lettura(BufferLS *);

void init_monitor(BufferLS *);
void remove_monitor(BufferLS *);


#endif
