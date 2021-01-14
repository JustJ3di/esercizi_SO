#include<pthread.h>
#include"header.h"



#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void *Produttore(void * p){

    //prima cosa d afare è sicuramente un casting

    prod_cons_t *pc = (prod_cons_t *)p;

    //ok ora posso lanciare la funzione produco

    Produco(pc);

    pthread_exit(NULL);

}


void *Consumatore(void *p){


    //prima cosa d afare è sicuramente un casting

    prod_cons_t *pc = (prod_cons_t *)p;
    int val;

    //ok ora posso lanciare la funzione consumo

    val = Consumo(pc);

    printf("Valore consumato = %d\n",val);    

    pthread_exit(NULL);


}


void Produco(prod_cons_t * pc){

    //per prima cosaa entro in sezione critic

    printf("produzione\n");

    pthread_mutex_lock(&pc->mutex);

    while (pc->numero_liberi == 0)
    {
        pthread_cond_wait(&pc->prod_cv,&pc->mutex);

    }

    int i = 0;
    while( i < 10 && pc->stato[i] != LIBERO){
        i++;
    }

    pc->stato[i] = IN_USO;
    pc->numero_liberi--;
    

    pthread_mutex_unlock(&pc->mutex);


    sleep(2);

    srand(123);

    pc->buff[i] = rand()%1000;

    pthread_mutex_lock(&pc->mutex);

    pc->stato[i] = OCCUPATO;
    pc->num_occupati++;

    pthread_cond_signal(&pc->cons_cv);

    pthread_mutex_unlock(&pc->mutex);


}



int Consumo(prod_cons_t * pc){

    pthread_mutex_lock(&pc->mutex);

    printf("consumazione\n");

    while (pc->num_occupati  == 0)
    {
        pthread_cond_wait(&pc->cons_cv,&pc->mutex);
    }

    int i = 0;

    while ( i < 10 && pc->stato[i] != OCCUPATO )
    {
        i++;
    }
    

    pc->stato[i] = IN_USO;
    pc->num_occupati--;


    pthread_mutex_unlock(&pc->mutex);

    sleep(2);

    int valore = pc->buff[i];

    pthread_mutex_lock(&pc->mutex); 

    pc->stato[i] = LIBERO;
    pc->numero_liberi++;

    pthread_cond_signal(&pc->prod_cv);


    pthread_mutex_unlock(&pc->mutex);

    return valore;

}