#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include"header.h"

void *generatore(void *m){

    MonitorVettore *mv = (MonitorVettore *)m;

    for (size_t i = 0; i < 10; i++)
    {
        elemento e = {rand()%11,rand()%11};
        genera(mv,e);
    }
    

    pthread_exit(NULL);

}

void *aggiornatore(void *m){

    Monitor *ms = (Monitor *)m;

    for (size_t i = 0; i < 10; i++)
    {
        elemento e = preleva(&(ms->mv));
     
        aggiorna(&(ms->mb),e);
        sleep(1);
    }
    

    pthread_exit(NULL);

}


void *destinatario(void *m){

    MonitorBuffer *mb = (MonitorBuffer *)m;

    for (size_t i = 0; i < 6; i++)
    {
        consulta(mb);
        sleep(2);
    }
    

    pthread_exit(NULL);

}


int main(){

    pthread_t gener,aggior;

    pthread_t desti[3];


    pthread_attr_t attr;


    srand(time(NULL));

    Monitor *m = (Monitor *)malloc(sizeof(Monitor));

    m->mb.num_lettori = m->mb.num_scrittori = 0;
    m->mb.wait_scrittori = m->mb.wait_lettori = 0;
    m->mv.coda = 0;
    m->mv.count = 0;
    m->mv.testa = 0;

    pthread_mutex_init(&(m->mb.mutex),NULL);
    pthread_mutex_init(&(m->mv.mutex),NULL);
    pthread_cond_init(&(m->mb.cv_scritt),NULL);
    pthread_cond_init(&(m->mb.cv_lett),NULL);
    pthread_cond_init(&(m->mv.cv_prod),NULL);
    pthread_cond_init(&(m->mv.cv_cons),NULL);

    pthread_attr_init(&attr);
    
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);


    pthread_create(&gener,&attr,generatore,(void *)&(m->mv));

    pthread_create(&aggior,&attr,aggiornatore,(void *)m);

    for (size_t i = 0; i < 3; i++)
    {    printf("sono qui    \n");
        pthread_create(&desti[i],&attr,destinatario,(void *)&(m->mb));
    }
    
    for (size_t i = 0; i < 3; i++)
    {
        pthread_join(desti[i],NULL);
    }

    pthread_join(gener,NULL);
    pthread_join(aggior,NULL);
    
    pthread_cond_destroy(&(m->mb.cv_scritt));
    pthread_cond_destroy(&(m->mb.cv_lett));
    pthread_cond_destroy(&(m->mv.cv_cons));    
    pthread_cond_destroy(&(m->mv.cv_cons));
    pthread_mutex_destroy(&(m->mv.mutex));
    pthread_mutex_destroy(&(m->mb.mutex));
   // pthread_attr_destroy(&attr);
    free(m);

    return 0;
}
