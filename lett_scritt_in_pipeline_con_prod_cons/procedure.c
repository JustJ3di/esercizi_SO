#include"header.h"

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<pthread.h>

void init_monitor(MonitorBuffer *l,MonitorVettore *p){

    pthread_cond_init(&(p->cv_prod),NULL);
    pthread_cond_init(&(p->cv_cons),NULL);
    pthread_mutex_init(&(p->mutex),NULL);

    p->count = 0;
    p->head = 0;
    p->tail = 0;


    pthread_cond_init(&(l->cv_lett),NULL);
    pthread_cond_init(&(l->cv_scrit),NULL);
    pthread_mutex_init(&(l->mutex),NULL);

    l->num_lett = 0;
    l->num_scrit = 0;
    l->wait_lett = 0;
    l->wait_scrit = 0;

}
void remove_monitor(MonitorBuffer *l,MonitorVettore *p){

    pthread_cond_destroy(&(p->cv_cons));
    pthread_cond_destroy(&(p->cv_prod));
    pthread_cond_destroy(&(l->cv_scrit));
    pthread_cond_destroy(&(l->cv_lett));
    pthread_mutex_destroy(&(p->mutex));
    pthread_mutex_destroy(&(p->mutex));


}


void *Generatore(void *p){

    Monitor *pc = (Monitor *)p;

    srand(time(NULL));

    for (size_t i = 0; i < 10; i++)
    {

        int a = rand()%10;
        int b = rand()%10;

        elemento e;

        e.a = a;
        e.b = b;

    
        genera(&(pc->v),e);

    }

    pthread_exit(NULL);

}

void *Aggiornatore(void *m){

    Monitor *mcs = (Monitor *)m;  //mcs = MONITOR CONSUMA SCRIVE



    for (size_t i = 0; i < 10; i++)
    {
        
        sleep(1);

        elemento  e = preleva(&(mcs->v));

        aggiorna(&(mcs->b),e);


    }

    pthread_exit(NULL);
}


void *Destinatario(void *l){

    Monitor *ls = (Monitor *)l;

    for (size_t i = 0; i < 6; i++)
    {

        sleep(2);
        consulta(&(ls->b));

    }

    pthread_exit(NULL);

}

void genera(MonitorVettore *pc,elemento e){

    printf("entro nel monitor_pc\n");

    pthread_mutex_lock(&(pc->mutex));

        
    while (pc->count == 5)
    {
        pthread_cond_wait(&(pc->cv_prod),&(pc->mutex));
    }

    printf("Produco\n");

    pc->vettore[pc->head] = e;

    printf("Produco il valore a = %d e b =%d   \n",e.a,e.b);

    pc->head = (pc->head +1)%5;

    pc->count++;
    printf("count = %d\n",pc->count);

    pthread_cond_signal(&(pc->cv_cons));
    pthread_mutex_unlock(&(pc->mutex));


} 

elemento preleva(MonitorVettore *pc){



    pthread_mutex_lock(&(pc->mutex));

    printf("consumo\n");

    while (pc->count == 0)
    {
        pthread_cond_wait(&(pc->cv_cons),&(pc->mutex));
    }
    

    elemento e = pc->vettore[pc->tail];

    printf("consumo il valore a=%d e b=%d \n",e.a,e.b);

    pc->tail = (pc->tail + 1)%5;

    pc->count--;

    pthread_cond_signal(&(pc->cv_prod));
    pthread_mutex_unlock(&(pc->mutex));

    return e;

}


void aggiorna(MonitorBuffer *ls,elemento e){

    pthread_mutex_lock(&(ls->mutex));

    while (ls->num_lett > 0 || ls->num_scrit > 0)
    {
        ls->wait_scrit++;
        pthread_cond_wait(&(ls->cv_scrit),&(ls->mutex));
        ls->wait_scrit--;
    }

    ls->num_scrit++;
    
    pthread_mutex_unlock(&(ls->mutex));

    //fai la fine scrittura

    ls->buffer = e;

    pthread_mutex_lock(&(ls->mutex));

    ls->num_scrit--;

    if (ls->wait_lett > 0)
    {
        pthread_cond_broadcast(&(ls->cv_lett));
    }else{
        pthread_cond_signal(&(ls->cv_scrit));
    }
    
    pthread_mutex_unlock(&(ls->mutex));

}

void consulta(MonitorBuffer *ls){

    pthread_mutex_lock(&(ls->mutex));
    
    while (ls->num_scrit > 0)
    {
        ls->wait_lett++;
        pthread_cond_wait(&(ls->cv_lett),&(ls->mutex));
        ls->wait_lett--;
    }
    

    ls->num_lett++;

    pthread_mutex_unlock(&(ls->mutex));


    printf("VALORE LETTO a = %d  b = %d  \n",ls->buffer.a,ls->buffer.b);    

    pthread_mutex_lock(&(ls->mutex));

    ls->num_lett--;

    if(ls->num_lett == 0){
        pthread_cond_signal(&(ls->cv_scrit));
    }

    pthread_mutex_unlock(&(ls->mutex));

}

