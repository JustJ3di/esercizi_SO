#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/sem.h>

#include "header.h"

int init_sem(key_t key,int nsem){

    int sem_id = semget(key,nsem,IPC_CREAT|0664);



    return sem_id;

}


void destroy_sem(int sem_id,int nsem){

    semctl(sem_id,nsem,IPC_RMID,0);

}

void Wait_sem(int sem_id,int num_sem){

    struct sembuf p = {num_sem,-1,0};

    semop(sem_id,&p,1);

}

void Signal_sem(int sem_id,int num_sem){

    struct sembuf p = {num_sem,1,0};

    semop(sem_id,&p,1);

}

void aggiorna_data(char new_data[10],esami *p,int sem_id){

    Wait_sem(sem_id,SYNC);


    Wait_sem(sem_id,MUTEX);

    printf("studenti prenotati %d \n",p->prenotati);

    p->prenotati = 0;

    Signal_sem(sem_id,MUTEX);


    strcpy(p->data,new_data);
    
    Signal_sem(sem_id,SYNC);
    

}

