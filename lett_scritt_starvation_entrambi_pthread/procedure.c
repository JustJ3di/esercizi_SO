#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include"header.h"


void *lettore(void *l){

    lett_scritt_t *ls = (lett_scritt_t *)l;

    inizio_lettura(ls);

    printf("valore letto %d \n",ls->buff);

    fine_lettura(ls);

    pthread_exit(NULL);

}



void *scrittore(void  *l){

    lett_scritt_t *ls = (lett_scritt_t *)l;

    srand(1233);

    inizio_scrittura(ls);

    ls->buff = rand()%12+1;

    fine_scrittura(ls);

    pthread_exit(NULL);

}



void inizio_lettura(lett_scritt_t *ls){

    pthread_mutex_lock(&ls->mutex);

    while(ls->n_scrittori > 0){

        ls->wait_lettori++;
        pthread_cond_wait(&ls->scrittori_cv,&ls->mutex);
        ls->wait_lettori--;

    }
    pthread_mutex_unlock(&ls->mutex);
}


void fine_lettura(lett_scritt_t * ls){

    pthread_mutex_lock(&ls->mutex);

    ls->n_lettori--;

    if (ls->n_lettori == 0)
    {
        pthread_cond_signal(&ls->scrittori_cv);
    }
    
    pthread_mutex_unlock(&ls->mutex);
}


void inizio_scrittura(lett_scritt_t *ls){

    pthread_mutex_lock(&ls->mutex);

    while(ls->n_lettori > 0|| ls->n_scrittori > 0){
        ls->wait_scrittori++;
        pthread_cond_wait(&ls->lettori_cv,&ls->mutex);
        ls->wait_scrittori--;
    }
    
    ls->n_scrittori++;

    pthread_mutex_unlock(&ls->mutex);

}


void fine_scrittura(lett_scritt_t *ls){

    pthread_mutex_lock(&ls->mutex);

    ls->n_scrittori--;

    if (ls->wait_scrittori > 0)
    {
        pthread_cond_signal(&ls->scrittori_cv);
    }else
    {
        pthread_cond_broadcast(&ls->lettori_cv);
    }
    
    pthread_mutex_unlock(&ls->mutex);
}