#include"header.h"

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include<pthread.h>


void init_monitor(BufferLS *ls){

    ls->num_lettori = 0;
    ls->num_scrittori = 0;
    ls->wait_lettori = 0;
    ls->wait_scrittori = 0;
    
    
    pthread_cond_init(&(ls->cv_lettore),NULL);
    pthread_cond_init(&(ls->cv_scrittore),NULL);
    pthread_mutex_init(&(ls->mutex),NULL);

}

void remove_monitor(BufferLS *ls){

    pthread_cond_destroy(&(ls->cv_lettore));
    pthread_cond_destroy(&(ls->cv_scrittore));
    pthread_mutex_destroy(&(ls->mutex));

}

void *Scrittore(void *l){

    Monitor *ls = (Monitor *)l;

    int val;

    srand(time(NULL));

    for (size_t i = 0; i < 3; i++)
    {
        sleep(3);

        val = rand()%10;

        Scrittura(&(ls->Buff_scritt),val);    
    
    }
    

    
    pthread_exit(NULL);
}


void *Lettore_Scrittore(void *l){

    Monitor *ls = (Monitor *)l;

    int val;

    for (size_t i = 0; i < 5; i++)
    {
        
        sleep(2);

        val = Lettura(&(ls->Buff_scritt));

        printf("lettori 2 e 3 leggono....  %d\n",val);

            
        Scrittura(&(ls->Buff_lett1),val);
        Scrittura(&(ls->Buff_lett2),val);

    }
    

    pthread_exit(NULL);
}

void *Lettore(void *l){

    Monitor *ls = (Monitor *)l;

    for (size_t i = 0; i < 10; i++)
    {
        sleep(1);
        printf(" lettura finale 1%d\n",Lettura(&(ls->Buff_lett1)));
        printf(" lettura finale 2%d\n",Lettura(&(ls->Buff_lett2)));
    
    }
    



    pthread_exit(NULL);

}

void Scrittura(BufferLS *ls,int val){

    pthread_mutex_lock(&(ls->mutex));

    printf("scrivo\n");

    while (ls->num_lettori > 0||ls->num_scrittori> 0)
    {
        ls->wait_scrittori++;
        pthread_cond_wait(&(ls->cv_scrittore),&(ls->mutex));
        ls->wait_scrittori--;
    }

    ls->num_scrittori++;

    pthread_mutex_unlock(&(ls->mutex));

    ls->buffer = val;

    pthread_mutex_lock(&(ls->mutex));

    printf("fine scrittura\n");
    
    ls->num_scrittori--;

    if (ls->wait_lettori > 0)
    {
        pthread_cond_broadcast(&(ls->cv_lettore));        
    }else{
        pthread_cond_signal(&(ls->cv_scrittore));
    }
    
    pthread_mutex_unlock(&(ls->mutex));

}



int Lettura(BufferLS *ls){


    pthread_mutex_lock(&(ls->mutex));
    printf("Inizio lettura\n");

    while (ls->num_scrittori > 0)
    {
        ls->wait_lettori++;
        pthread_cond_wait(&(ls->cv_lettore),&(ls->mutex));
        ls->wait_lettori--;
    }
    
    ls->num_lettori++;

    pthread_mutex_unlock(&(ls->mutex));

    int val = ls->buffer;

    pthread_mutex_lock(&(ls->mutex));

    printf("fine lettura  \n");

    ls->num_lettori--;

    if (ls->num_lettori == 0)
    {
        pthread_cond_signal(&(ls->cv_scrittore));
    }
    
    pthread_mutex_unlock(&(ls->mutex));

    return val;
}

