#ifndef HEADER_H
#define HEADER_H

#define N_OPER 10

#define DIM 3
#include<semaphore.h>

typedef struct header
{
    int vet[3];
    int head;
    int tail;
    sem_t mutex_p;
    sem_t mutex_c;
    sem_t spazio_disp;
    sem_t mex_disp;
}Buff;

void produci(Buff*,int);
int consuma(Buff*);


#endif
