#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>



#define REQUEST_TO_SEND 1
#define OK_TO_SEND 2

typedef  int mex;

#define PATH1 "."
#define PATH2 'a'

typedef struct mex_t
{
    
    long type;

    mex msg;

}Messaggio;

typedef struct{

    pthread_mutex_t mutex;

    int rts_queue;
    int oks_queue;
    int queue;


}proteggere_t;


void *server_1(void *);
void *server_2(void *);

#endif
