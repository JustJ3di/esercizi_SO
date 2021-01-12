#ifndef HEADER_H
#define HEADER_H

#include"monitor.h"

#define DIM 8
#define PRODUTTORI 5
#define CONSUMATORI 5



#define CV_PRODUTTORI 0
#define CV_CONSUMATORI 1

typedef struct header{
    
    int head;
    int tail;
    int count;

    int buff[DIM];

    Monitor M;

}prod_cons_t;


void Produttore(prod_cons_t *);

void Consumatore(prod_cons_t *);




#endif
