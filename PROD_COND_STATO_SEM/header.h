#ifndef HEADER_H
#define HEADER_H

#include<sys/types.h>

//semafori

#define MUTEX_PROD 0
#define MUTEX_CONS 1
#define SPAZIO_DISP 2
#define MESSAGGIO_DISP 3


int init_sem(key_t);
void Wait_sem(int,int);
void Signal_sem(int,int);



//shared_memory

#define PATH1 "."
#define PATH2 'a'

int init_shm(key_t);

void shm_destroy(int);


// buffer

#define POSTI_TOTALI 80

#define OCCUPATO 0
#define LIBERO   1
#define IN_USO   3

typedef struct header
{
    
    int stato[POSTI_TOTALI];
    int  id_utente[POSTI_TOTALI];

    int disp;


}posto;


//cliente

void cliente(int,posto *);


#endif