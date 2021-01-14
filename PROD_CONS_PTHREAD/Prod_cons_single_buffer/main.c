#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include"header.h"



int main(){


    pthread_t thread[NUM_THREADS];

    prod_cons_t *ps = (prod_cons_t *)malloc(sizeof(prod_cons_t));

    pthread_mutex_init(&ps->mutex,NULL);
    pthread_cond_init(&ps->mex_disp,NULL);
    pthread_cond_init(&ps->spa_disp,NULL);

    ps->cons_ok = 0;
    ps->prod_ok = 1;



    
    for (int i = 0; i < NUM_THREADS ; i++)
    {
        if (i%2 == 0)
        {
                
            pthread_create(&thread[i],NULL,Produco,(void *)ps);
        
        }else
            pthread_create(&thread[i],NULL,Consumo,(void*)ps);
        
    }
    
    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thread[i],NULL);        /* code */
    }
  
    pthread_mutex_destroy(&ps->mutex);
    pthread_cond_destroy(&ps->mex_disp);
    pthread_cond_destroy(&ps->spa_disp);

    pthread_exit(NULL);

    free(ps);
    

    return 0;
}
