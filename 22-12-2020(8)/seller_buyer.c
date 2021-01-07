#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "seller_buyer.h"


int main(){
    
    int i;
    
    pthread_t seller_threads[2];
    pthread_t buyer_threads[5];
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    
    srand(time(NULL));
    
    /* TBD: Aggiungere codice per l'allocazione della struttura LettScritt */

    LettScritt *m = (LettScritt *)malloc(sizeof(LettScritt));
    
    m->quotazione_oro = 0;
    m->quotazione_argento = 0;
   

    /* TBD: Aggiungere codice per l'inizializzazione della variabili in LettScritt utilizzate per la sincronizzazione */

    m->num_lett = m->num_scritt = 0;
    m->wait_scritt = 0;
    pthread_mutex_init(&(m->mutex),NULL);
    pthread_cond_init(&(m->cv_lettori),NULL);
    pthread_cond_init(&(m->cv_scrittori),NULL);

    
    for(i=0;i<2;i++){
         /* TBD: creazione dei threads seller */
         pthread_create(&seller_threads[i],&attr,seller,(void *)m);
    }
    
    
    for(i=0;i<5;i++){
        /* TBD: creazione dei threads buyer */
        pthread_create(&buyer_threads[i],&attr,buyer,(void *)m);
    }
    
    
    for(i=0;i<2;i++){
        /* TBD: Join dei threads seller */
        pthread_join(buyer_threads[i],NULL);
        printf("seller_threads %d terminato\n",i+1);
    }
    
    
    for(i=0;i<5;i++){
        /* TBD: Join dei threads seller */
        pthread_join(seller_threads[i],NULL);
        printf("buyer_threads %d terminato\n",i+1);
    }
    
    
    /* TBD: deallocazione monitor e relative variabili usate per la sincronizzazione */
    pthread_attr_destroy(&attr);

    pthread_mutex_destroy(&(m->mutex));
    pthread_cond_destroy(&(m->cv_lettori));
    pthread_cond_destroy(&(m->cv_scrittori));

    free(m);

    
    pthread_exit(NULL);
}

