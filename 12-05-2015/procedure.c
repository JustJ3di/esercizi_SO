#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include"header.h"



void inseriscivolo(gestionevoli *g,int identificativo){

    pthread_mutex_lock(&(g->mutex));

    while (g->occupati == 3)
    {
        pthread_cond_wait(&(g->cv_produttori),&(g->mutex));
    }
    
    int i = 0;

    while (i <= 3 && g->vett_stato[i] != LIBERO  )
    {
        i++;
    }
    
    g->vett_stato[i] = IN_USO;
    g->liberi--;

    pthread_mutex_unlock(&(g->mutex));

    g->vettori_voli[i].identificativo = identificativo;
    printf("id inserito <%d>\n",identificativo);

    pthread_mutex_lock(&(g->mutex));
    g->occupati++;
    g->vett_stato[i] = OCCUPATO;

    

    pthread_mutex_unlock(&(g->mutex));


}
void rimuovivolo(gestionevoli *g,int identificativo){

    

    pthread_mutex_lock(&(g->mutex));
    
    printf("rimuovo \n");

    int j = 0;

    for (size_t i = 0; i < 3; i++)
    {
        if (g->vett_stato[i] != LIBERO && i == identificativo)
        {
            j = i;
        }
        
    }
    
    
    g->vett_stato[j] = IN_USO;
    g->occupati--;

    pthread_mutex_unlock(&(g->mutex));

    printf("volo <%d>   rimosso   \n",identificativo);

    pthread_mutex_lock(&(g->mutex));
    g->liberi++;
    g->vett_stato[j] =LIBERO;

    pthread_cond_signal(&(g->cv_produttori));

    pthread_mutex_unlock(&(g->mutex));


}
void aggiornavolo(gestionevoli *g,int identificativo,int quota){

    pthread_mutex_lock(&(g->mutex));

    int j= 0;
    for (size_t i = 0; i <= 3; i++)
    {
        if (g->vett_stato[i] == OCCUPATO)
        {
            j = i;   
        }

    }
    g->vett_stato[j] = IN_USO;
    g->vettori_voli[j].quota = quota;
    g->vett_stato[j] = OCCUPATO;

    printf("nuova quota volo id <%d>  || <%d>  \n",identificativo,quota);
    
    //pthread_cond_signal(&(g->cv_produttori));

    pthread_mutex_unlock(&(g->mutex));

}