#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#include"header.h"

void *produttore(void *p){

    Buff *b = (Buff *)p;

    srand(time(NULL));
    for (size_t i = 0; i < N_OPER; i++)
    {
    
        printf("Produzione\n");
        int val = rand()%110+3;

        produci(b,val);

    }

    pthread_exit(NULL);

}

void *consumatore(void *p){

    Buff *b = (Buff *)p;
    
    for(int i = 0;i<N_OPER;i++)
        printf("valore consumato <%d>\n",consuma(b));
    

    pthread_exit(NULL);
}

int main(){

    pthread_t thread[10];


    Buff *b = (Buff *)malloc(sizeof(Buff));


//init
    sem_init(&b->mutex_c,0,1);
    sem_init(&b->mutex_p,0,1);
    sem_init(&b->spazio_disp,0,DIM);
    sem_init(&b->mex_disp,0,0);

    b->head = b->tail = 0;


//create thread
    for (size_t i = 0; i < 10; i++)
    {
       
        
        if (i%2==0)
        {
            pthread_create(&thread[i],NULL,produttore,(void *)b);   
            sleep(1);         
        }else{
            pthread_create(&thread[i],NULL,consumatore,(void *)b);
            sleep(1);
        }
        
    
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(thread[i],NULL);
    }
    

    sem_destroy(&b->mutex_c);
    sem_destroy(&b->mutex_p);
    sem_destroy(&b->spazio_disp);
    sem_destroy(&b->mex_disp);
    
    free(b);
    
    pthread_exit(NULL);

}
