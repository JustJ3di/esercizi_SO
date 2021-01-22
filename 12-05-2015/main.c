#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>


#include"header.h"



void *thread(void *pc){

    srand(time(NULL));
    gestionevoli *g = (gestionevoli *)pc;


    printf("inserimento volo...<%d>\n",g->id);
    inseriscivolo(g,g->id);
    sleep(1);    

    printf("Aggiornamento...\n");
    aggiornavolo(g,g->id,1000);
    sleep(rand()%3+1);
    printf("Aggiornamento.. \n");
    aggiornavolo(g,g->id,2000);
    sleep(rand()%3+1);
    printf("Aggiornamento.\n");
    aggiornavolo(g,g->id,1000);
    sleep(rand()%3+1);


    rimuovivolo(g,g->id);
    sleep(1);

    pthread_exit(NULL);

}

int main(){

    pthread_t voli[5];

    gestionevoli *g = (gestionevoli *)malloc(sizeof(gestionevoli));

    g->occupati = 0;
    g->liberi = 3;

    pthread_mutex_init(&(g->mutex),NULL);

    pthread_cond_init(&(g->cv_consumatori),NULL);

    pthread_cond_init(&(g->cv_produttori),NULL);

    for (g->id = 0; g->id < 5;g->id++)
    {
        
        pthread_create(&voli[g->id],NULL,thread,(void *)g);    

    }
    

    for (size_t i = 0; i < 5; i++)
    {
        pthread_join(voli[i],NULL);
    }
    

    pthread_mutex_destroy(&(g->mutex));
    pthread_cond_destroy(&(g->cv_consumatori));
    pthread_cond_destroy(&(g->cv_produttori));

    free(g);

    return 0;
}