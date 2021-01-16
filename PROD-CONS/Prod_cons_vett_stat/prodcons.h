#ifndef PROD_CONS
#define PROD_CONS

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#define NUM_PROD 5
#define NUM_CONS 5
#define DIM 3


//stati del buffer di stato  :

#define BUFFER_VUOTO 0
#define BUFFER_IN_USO 1
#define BUFFER_PIENO 2


typedef struct prodcons{

    int buffer[DIM];
    int vett_stat[DIM];

}prodcons_t;


void produttore(prodcons_t *ps,int id_sem);


void consumatore(prodcons_t *ps,int id_sem);


#endif