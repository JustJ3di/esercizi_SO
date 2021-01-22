#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include"header.h"

void *Produttore(void *p){

    Monitorelaborazioni *pc = (Monitorelaborazioni *)p;

    for(int i = 0;i<3;i++)
        Produci(pc);

    pthread_exit(NULL);


}

void *Consumatore(void *p){

    Monitorelaborazioni *pc = (Monitorelaborazioni *)p;

    for(int i = 0;i<6;i++)
        Consuma(pc);

    pthread_exit(NULL);

}

int main(){

    pthread_t richiedenti[4];
    pthread_t elaboratori[2];

    Monitorelaborazioni *pc = (Monitorelaborazioni *)malloc(sizeof(Monitorelaborazioni));

    init_monitor(pc);

    for (size_t i = 0; i < 4; i++)
    {
        pthread_create(&richiedenti[i],NULL,Produttore,(void *)pc);
    }

    for (size_t i = 0; i < 2; i++)
    {
        pthread_create(&elaboratori[i],NULL,Consumatore,(void *)pc);
    }
    

    for (size_t i = 0; i < 4; i++)
    {
        pthread_join(richiedenti[i],NULL);

    }

    for (size_t i = 0; i < 2; i++)
    {
        pthread_join(elaboratori[i],NULL);
    }
    
    


    remove_monitor(pc);

    free(pc);


}