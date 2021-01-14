#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include"header.h"

void *Produco(void *ps){

    printf("IO PRODUCO\n");
    prod_cons_t *px = (prod_cons_t *)ps;

    srand(123);
 

    //for(int i  = 0;i<3;i++)
    {
        int msg = rand()%10;        

        Produttore(px,msg);

    }

    pthread_exit(NULL);
   
}


void *Consumo(void *ps){

    printf("IO CONSUMO\n");

    prod_cons_t *px = (prod_cons_t *)ps;
       
    //for (size_t i = 0; i < 3; i++)
    {
        Consumatore(px);        
    }
    

    pthread_exit(NULL);

}

void Produttore(prod_cons_t* px,int mex){

    //enter in monitore

    pthread_mutex_lock(&px->mutex);

    while(px->prod_ok == 0){
        pthread_cond_wait(&px->spa_disp,&px->mutex);  //questa wait_cond rilascia anche il mutex
    }
    //prod
    px->buff = mex;

    //update var_cond

    px->cons_ok = 1;
    px->prod_ok = 0;


    //signal consumatori
    pthread_cond_signal(&px->mex_disp);

    //leave monitor
    pthread_mutex_unlock(&px->mutex);

}

void Consumatore(prod_cons_t* px){

    pthread_mutex_lock(&px->mutex);

    if(px->cons_ok == 0)
        pthread_cond_wait(&px->mex_disp,&px->mutex);

    printf("Valore consumato è %d\n",px->buff);

    px->cons_ok = 0;
    px->prod_ok = 1;

    pthread_cond_signal(&px->spa_disp);

    pthread_mutex_unlock(&px->mutex);    


}