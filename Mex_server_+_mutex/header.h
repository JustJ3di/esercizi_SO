#ifndef HEADER_H
#define HEADER_H

#define K1_PATH "."
#define K2_PATH 'a'

#include<sys/types.h>

#define MEX_CLIENT 4

#define N_CLIENT 3
#define N_SERVER 3

#define MUTEX 0

typedef struct 
{

    int valore1;
    int valore2;


}shared;

typedef struct{

    long type_mex;

    int VAL1;
    int VAL2;


}Messaggio;


int init_shm(key_t);

int init_queue(key_t);

void invio(int,Messaggio);



int init_sem(key_t);

int Wait_sem(int,int);

int Signal_sem(int,int);


#endif
