#include<pthread.h>
#include"header.h"
#include<stdlib.h>
#include<stdio.h>

void Inizializza(GestioneIO *g){

    pthread_mutex_init(&(g->mutex),NULL);
    pthread_cond_init(&(g->cv_prod),NULL);


    g->count = 0;
    g->coda = 0;
    g->testa = 0;

}


void Rimuovi(GestioneIO *g){

    pthread_mutex_destroy(&(g->mutex));

    pthread_cond_destroy(&(g->cv_prod));


}
//copia_due_buffer
void copia_buffer(Buffer *dst,Buffer *src){

    dst->dato = src->dato;
    dst->indirizzo = src->indirizzo;

}



void Produci(GestioneIO *g,Buffer *b){

    pthread_mutex_lock(&(g->mutex));

    while (g->count == 10)
    {
        pthread_cond_wait(&(g->cv_prod),&(g->mutex));
    }
    

    copia_buffer(&(g->vettore[g->testa]),b);

    printf("Prodotto dato <%d>  indirizzo <%d>\n",b->dato,b->indirizzo);

    g->testa = (g->testa + 1)%10;
    g->count++;
    


    pthread_mutex_unlock(&(g->mutex));

}


int Consuma(GestioneIO *g,Buffer *b){

    pthread_mutex_lock(&(g->mutex));

    while (g->count == 0)
    {   
        pthread_mutex_unlock(&(g->mutex));
        return 1;
        
    }


    copia_buffer(b,&(g->vettore[g->coda]));

    g->coda = (g->coda +1)%10;
    g->count--;
    
    pthread_cond_signal(&(g->cv_prod));
    pthread_mutex_unlock(&(g->mutex));

    return 0;

}