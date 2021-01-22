#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

void init_monitor(Monitorelaborazioni *pc){

    pthread_cond_init(&(pc->cv_consumatori),NULL);
    pthread_cond_init(&(pc->cv_produttori),NULL);
    pthread_mutex_init(&(pc->mutex),NULL);
    pc->occupati = 0;
    pc->liberi = DIM;
    for (size_t i = 0; i < DIM; i++)
    {
        pc->stato[i] = LIBERO;
    }
    

}



void remove_monitor(Monitorelaborazioni *pc){

    pthread_mutex_destroy(&(pc->mutex));
    pthread_cond_destroy(&(pc->cv_consumatori));
    pthread_cond_destroy(&(pc->cv_produttori));

}


void Produci(Monitorelaborazioni *pc){

    pthread_mutex_lock(&(pc->mutex));

    while(pc->liberi == 0){
        pthread_cond_wait(&(pc->cv_produttori),&(pc->mutex));
    }

    int i = 0;


    while (i <= DIM && pc->stato[i] != LIBERO)
    {
        
        i++;
    
    }

    pc->liberi--;
    pc->stato[i] = IN_USO;

    pthread_mutex_unlock(&(pc->mutex));

    srand(time(NULL));

    pc->elaborazioni[i].totale_operandi = rand()%3 + 2;

    for (size_t k = 0; k < pc->elaborazioni[i].totale_operandi; k++)
    {
        pc->elaborazioni[i].operandi[k] = rand()%10;
        printf("operando  %d  sul totale di %d , i  %d\n",pc->elaborazioni[i].operandi[k],pc->elaborazioni[i].totale_operandi,i);
    }



    pthread_mutex_lock(&(pc->mutex));

    

    pc->stato[i]= OCCUPATO;
    pc->occupati++;

    pthread_cond_signal(&(pc->cv_consumatori));
    pthread_mutex_unlock(&(pc->mutex));

}


void Consuma(Monitorelaborazioni *pc){

    pthread_mutex_lock(&(pc->mutex));

    while (pc->occupati == 0)
    {
        pthread_cond_wait(&(pc->cv_consumatori),&(pc->mutex));
    }


    int pos = 0;
    int min = 10;

    for (size_t i = 0; i < DIM; i++)
    {
        
        if (pc->stato[i] == OCCUPATO && min > pc->elaborazioni[i].totale_operandi )
        {
            
            min = pc->elaborazioni[i].totale_operandi;
            pos = i;

        }
        

    }
    

    pc->occupati--;
    pc->stato[pos] = IN_USO;
    
    pthread_mutex_unlock(&(pc->mutex));

    int sum = 0;
    sleep(pc->elaborazioni[pos].totale_operandi);
    for (size_t k = 0; k < pc->elaborazioni[pos].totale_operandi ; k++)
    {

        sum = pc->elaborazioni[pos].operandi[k] + sum ;

    }




    printf("sum <%d>  , i %d\n",sum,pos);
    

    pthread_mutex_lock(&(pc->mutex));

    pc->stato[pos] = LIBERO;
    pc->liberi++;

    pthread_cond_signal(&(pc->cv_produttori));
    pthread_mutex_unlock(&(pc->mutex));
    

}



