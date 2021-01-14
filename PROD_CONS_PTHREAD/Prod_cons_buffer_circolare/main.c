#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include"header.h"

int main(){

    pthread_t thread[DIM];

    Prod_cons_t * p = (Prod_cons_t *)malloc(sizeof(Prod_cons_t));

    pthread_mutex_init(&p->mutex,NULL);
    pthread_cond_init(&p->cv_consumatore,NULL);
    pthread_cond_init(&p->cv_produttore,NULL);

    p->count = 0;

    p->consumo_in_coda = p->procuco_in_testa = 0;

    for (int i = 0; i < DIM; i++)
    {
        if (i%2 == 0)
        {
            pthread_create(&thread[i],NULL,Produttore,(void*)p);

        }else
        {
                pthread_create(&thread[i],NULL,Consumatore,(void*)p);
        }        
        
    }


    for (size_t i = 0; i < DIM; i++)
    {
        pthread_join(thread[i],NULL);
    }

    
    pthread_mutex_destroy(&p->mutex);

    pthread_cond_destroy(&p->cv_consumatore);
    pthread_cond_destroy(&p->cv_produttore);

    pthread_exit(NULL);

    return 0;
}