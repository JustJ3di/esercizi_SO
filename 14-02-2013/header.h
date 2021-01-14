#ifndef HEADER_H
#define HEADER_H

#include<sys/types.h>

#define PATH1 "."
#define PATH2 'a'

#define SYNC 0
#define MUTEX 1

typedef struct 
{

    int prenotati;
    int num_lettori;

    char data[16];
    

}esami;

int init_sem(key_t,int);

void Wait_sem(int,int);

void Signal_sem(int,int);

void destroy_sem(int,int);

void aggiorna_data(char [16],esami *,int);

#endif
