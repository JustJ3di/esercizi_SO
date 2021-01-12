#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include"header.h"

int main(){

    pthread_t thread[7];

    Monitor *l = (Monitor *)malloc(sizeof(Monitor));

    init_monitor(&(l->Buff_lett1));
    init_monitor(&(l->Buff_lett2));
    init_monitor(&(l->Buff_scritt));


    


    pthread_create(&thread[0],NULL,Scrittore,(void *)l);

    for (size_t i = 1; i < 3; i++)
    {
        pthread_create(&thread[i],NULL,Lettore_Scrittore,(void *)l);

    }


    for (size_t i = 3 ; i < 7; i++)
    {
        pthread_create(&thread[i],NULL,Lettore,(void *)l);
    }
    



    for (size_t i = 0; i < 7; i++)
    {
        pthread_join(thread[i],NULL);
    }
    

    remove_monitor(&(l->Buff_lett1));
    remove_monitor(&(l->Buff_lett2));
    remove_monitor(&(l->Buff_scritt));
    
    free(l);
    

    return 0;
}
