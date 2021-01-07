#ifndef PROD_CONS
#define PROD_CONS

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#define NUM_PROD 5
#define NUM_CONS 5
#define DIM 3

typedef struct prodcons{

    int buffer[DIM];

    int testa;
    int coda;

}prodcons_t;


void produttore(prodcons_t *ps,int id_sem);


void consumatore(prodcons_t *ps,int id_sem);


#endif
