#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<pthread.h>

#include"header.h"

int main(int argc,char *argv[]){


    pthread_t thread[10];  // 5 thread lettori e 5 thread scrittori
    
    lett_scritt_t *l;

    l = (lett_scritt_t *)malloc(sizeof(lett_scritt_t));

    l->n_lettori = 0;
    l->n_scrittori = 0;
    l->wait_scrittori = 0;
    l->wait_lettori = 0;

    pthread_mutex_init(&l->mutex,NULL);
    pthread_cond_init(&l->lettori_cv,NULL);
    pthread_cond_init(&l->scrittori_cv,NULL);


    for (size_t i = 0; i < 10; i++)
    {
        if(i%2 == 0)
            pthread_create(&thread[i],NULL,scrittore,(void *)l);
        else
            pthread_create(&thread[i],NULL,lettore,(void *)l);
        
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(thread[i],NULL);
    }
    

    pthread_mutex_destroy(&l->mutex);
    pthread_cond_destroy(&l->scrittori_cv);
    pthread_cond_destroy(&l->lettori_cv);


    pthread_exit(NULL);    

    return 0;
}