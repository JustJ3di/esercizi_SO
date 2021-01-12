#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include"header.h"
#include"header.h"

int main(){

    pthread_t generatore;
    pthread_t aggiornatore;
    pthread_t destinatario[3];

    Monitor *m = (Monitor *)malloc(sizeof(Monitor));


    //init_monitor
    init_monitor(&(m->b),&(m->v));


    pthread_create(&generatore,NULL,Generatore,(void*)m);

    

    pthread_create(&(aggiornatore),NULL,Aggiornatore,(void *)m);


    for (size_t i = 0; i < 3; i++)
    {
        pthread_create(&destinatario[i],NULL,Destinatario,(void *)m);
    }
    
    for (size_t i = 0; i < 3; i++)
    {
        pthread_join(destinatario[i],NULL);
    }
    
    pthread_join(generatore,NULL);

    pthread_join(aggiornatore,NULL);

    remove_monitor(&(m->b),&(m->v));

    free(m);
    return 0;
}