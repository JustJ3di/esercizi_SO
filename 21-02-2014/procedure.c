#include"header.h"
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>


void inizializza(MonitorTreno *m){

    pthread_mutex_init(&(m->mutex),NULL);
    pthread_cond_init(&(m->cv_lettore),NULL);
    pthread_cond_init(&(m->cv_scittore),NULL);

    m->num_lettori = 0;
    m->num_scrittori = 0;
    m->wait_lettori = 0;
    m->wait_scrittori = 0;

}
void rimuovi(MonitorTreno *m){

    pthread_mutex_destroy(&(m->mutex));
    pthread_cond_destroy(&(m->cv_lettore));
    pthread_cond_destroy(&(m->cv_scittore));

}
int leggi_stazione(MonitorTreno *m){

    int stazione_letta;

    pthread_mutex_lock(&(m->mutex));

    while (m->num_scrittori > 0)
    {
        m->wait_lettori++;
        pthread_cond_wait(&(m->cv_lettore),&(m->mutex));
        m->wait_lettori--;
    }
    

    m->num_lettori++;

    pthread_mutex_unlock(&(m->mutex));

    stazione_letta = m->stazione;

    pthread_mutex_lock(&(m->mutex));

    m->num_lettori--;

    if (m->num_lettori == 0)
    {
        pthread_cond_signal(&(m->cv_scittore));
    }
    
    pthread_mutex_unlock(&(m->mutex));

    return stazione_letta;

}
void scrivi_stazione(MonitorTreno *m){

    pthread_mutex_lock(&(m->mutex));

    while (m->num_lettori > 0 || m->num_scrittori > 0)
    {
        m->wait_scrittori++;
        pthread_cond_wait(&(m->cv_scittore),&(m->mutex));
        m->wait_scrittori--;
    }
    
    m->num_scrittori++;

    pthread_mutex_unlock(&(m->mutex));

    m->stazione = rand()%11;

    pthread_mutex_lock(&(m->mutex));

    m->num_scrittori--;

    if (m->wait_scrittori > 0)
    {
        pthread_cond_signal(&(m->cv_scittore));
    }else
    {
        pthread_cond_broadcast(&(m->cv_lettore));
    }
    
    pthread_mutex_unlock(&(m->mutex));

}
