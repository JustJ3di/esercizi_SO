#include "prodcons.h"

#include <stdio.h>


void inizializza(MonitorStreaming * m) {

    /* TBD: Inizializzare il monitor */
    pthread_mutex_init(&(m->mutex),NULL);
    pthread_cond_init(&(m->cv_cons),NULL);
    pthread_cond_init(&(m->cv_prod),NULL);

    m->coda = m->testa = 0;
    m->count = 0;

}

void produci(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */

    pthread_mutex_lock(&(m->mutex));

    while (m->count == DIM)
    {
        pthread_cond_wait(&(m->cv_prod),&(m->mutex));
    }
    


    printf("Produzione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);

    /* TBD */m->vettore[m->testa][0][0] = f[0][0];
    /* TBD */ m->vettore[m->testa][0][1]= f[0][1];
    /* TBD */ m->vettore[m->testa][1][0]= f[1][0];
    /* TBD */ m->vettore[m->testa][1][1]= f[1][1];

    m->testa = (m->testa +1)%DIM;
    m->count++;

    pthread_cond_signal(&(m->cv_cons));
    pthread_mutex_unlock(&(m->mutex));


}

void consuma(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    pthread_mutex_lock(&(m->mutex));

    while (m->count == 0)
    {
        pthread_cond_wait(&(m->cv_cons),&(m->mutex));
    }
    
    

    f[0][0] = m->vettore[m->coda][0][0];  /* TBD */
    f[0][1] = m->vettore[m->coda][0][1];  /* TBD */
    f[1][0] = m->vettore[m->coda][1][0];   /* TBD */
    f[1][1] = m->vettore[m->coda][1][1];/* TBD */

    m->coda= (m->coda +1)%DIM;
    m->count--;

    printf("Consumazione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);

    pthread_cond_signal(&(m->cv_prod));

    pthread_mutex_unlock(&(m->mutex));

}

void bufferizza(MonitorStreaming * m, int n) {


    /* TBD: Completare il metodo */
    pthread_mutex_lock(&(m->mutex));

    while (m->count < n)
    {
        pthread_cond_wait(&(m->cv_cons),&(m->mutex));
    
        pthread_mutex_unlock(&(m->mutex));
    }
    




}

void distruggi(MonitorStreaming * m) {

    /* TBD: Completare il metodo */
    pthread_mutex_destroy(&(m->mutex));
    pthread_cond_destroy(&(m->cv_cons));
    pthread_cond_destroy(&(m->cv_prod));

}
