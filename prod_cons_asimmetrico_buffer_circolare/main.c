#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include"header.h"

int main(){

    pthread_t cons_thread[2];
    pthread_t prod_thread[4];

    GestioneIO *p = (GestioneIO *)malloc(sizeof(GestioneIO));

    Inizializza(p);


    for (size_t i = 0; i < 2; i++)
    {
        
        pthread_create(&cons_thread[i],NULL,Consumatore,(void *)p);

    }


    for (size_t i = 0; i < 4; i++)
    {
        
        pthread_create(&prod_thread[i],NULL,Produttore,(void *)p);

    }
    
    for (size_t i = 0; i < 2; i++)
    {
    
        pthread_join(cons_thread[i],NULL);
    
    }
    
    
    for (size_t i = 0; i < 4; i++)
    {
    
        pthread_join(prod_thread[i],NULL);
    
    }
    
    
    pthread_cond_destroy(&(p->cv_produttore));
    
    pthread_mutex_destroy(&(p->mutex));

    free(p);

    return 0;
}
