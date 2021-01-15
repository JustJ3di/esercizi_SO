#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include"header.h"

void genera(MonitorVettore *v,elemento e){


    pthread_mutex_lock(&(v->mutex));

    while (v->count == 5)
    {
        pthread_cond_wait(&(v->cv_prod),&(v->mutex));
    }


    v->vettore[v->testa].a = e.a;
    v->vettore[v->testa].b = e.b;

    printf("Genero %d %d\n",v->vettore[v->testa].a,v->vettore[v->testa].b);

    v->testa = (v->testa + 1)%DIM;

    v->count++;
    
    pthread_cond_signal(&(v->cv_cons));

    pthread_mutex_unlock(&(v->mutex));


}
elemento preleva(MonitorVettore *v){

    elemento e;

    pthread_mutex_lock(&(v->mutex));

    while (v->count == 0)
    {
        pthread_cond_wait(&(v->cv_cons),&(v->mutex));
    }
    

    e.a = v->vettore[v->coda].a;
    e.b = v->vettore[v->coda].b;

    v->coda = (v->coda + 1)%DIM;
    v->count--;

    pthread_cond_signal(&(v->cv_prod));
    pthread_mutex_unlock(&(v->mutex));
    
    return e;

}
void aggiorna(MonitorBuffer *b,elemento e){



    pthread_mutex_lock(&(b->mutex));

    while (b->num_scrittori > 0 || b->num_lettori > 0)
    {
        b->wait_scrittori++;
        pthread_cond_wait(&(b->cv_scritt),&(b->mutex));
        b->wait_scrittori--;
    }
    
    b->num_scrittori++;

    pthread_mutex_unlock(&(b->mutex));

    printf("aggiorna  \n");

    b->buffer.a = e.a;
    b->buffer.b = e.b;

    pthread_mutex_lock(&(b->mutex));


    b->num_scrittori--;

    if (b->wait_scrittori > 0)
    {
        pthread_cond_signal(&(b->cv_scritt));
    }else
    {
        pthread_cond_broadcast(&(b->cv_lett));
    }

    pthread_mutex_unlock(&(b->mutex));
    

}


void consulta(MonitorBuffer *b){

    printf("Consulto\n");
    pthread_mutex_lock(&(b->mutex));

    while (b->num_scrittori>0)
    {
        b->wait_lettori++;
        pthread_cond_wait(&(b->cv_lett),&(b->mutex));
        b->wait_lettori--;
    }
    
    b->num_lettori++;

    pthread_mutex_unlock(&(b->mutex));

    printf("letti valori a <%d> e b <%d>\n",b->buffer.a,b->buffer.b);

    pthread_mutex_lock(&(b->mutex));

    b->num_lettori--;

    if (b->num_lettori == 0)
    {
        pthread_cond_signal(&(b->cv_scritt));
    }

    pthread_mutex_unlock(&(b->mutex));    

}
