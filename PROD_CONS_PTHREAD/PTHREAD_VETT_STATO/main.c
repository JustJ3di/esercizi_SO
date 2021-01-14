#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


#include"header.h"

int main(){

    pthread_t thread[10];   //decido di scegliere 10 thread quindi un 1 thread per ogni valore presente nel buffer
    
    //per prima cosa devo richiamarmi in memoria la struttura dati create nell header

    prod_cons_t   *p = (prod_cons_t *)malloc(sizeof(struct prod_cons)); 
    
    //ora inizializzo le variabuli che mi servono per il monitor quindi ovviamente la mia variabile mutex per la mutua esclusione in ingresso e 2 variabili condition

    //metto il & perchè sto passando il riferimento ovviamente

    //qui devo inizializzare anche il vettore di stato a libero

    for (size_t i = 0; i < 10; i++)
    {
        p->stato[i] = LIBERO;
    }
    p->numero_liberi = DIM_BUFF;
    p->num_occupati = 0;
    

    pthread_mutex_init(&p->mutex,NULL);
    pthread_cond_init(&p->cons_cv,NULL);
    pthread_cond_init(&p->prod_cv,NULL);


    //ok posso creare o mieri thread che sono di default joinabili


    for (size_t i = 0; i < 10; i++)  //QUI LANCERO IL MIO CICLO CHE MI CREA 5 THREAD CONSUMATORI E 5 TRHEAD PRODUTTORI
    {                                 
        if (i%2 == 0)
        {
            pthread_create(&thread[i],NULL,Produttore,(void *)p);
        
        }else{

            pthread_create(&thread[i],NULL,Consumatore,(void *)p);

        }
        
    }


    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(thread[i],0);
    }
    

    
    pthread_exit(NULL);


    return 0;

}