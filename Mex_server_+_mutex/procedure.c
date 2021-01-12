#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/sem.h>

#include"header.h"


int init_shm(key_t key){

    int shm_id = shmget(key,sizeof(shared),IPC_CREAT|0664);

    if (shm_id < 0)
    {
        perror("shm error       \n");
        exit(1);
    }


    return shm_id;
}


int init_queue(key_t key){

    int queue = msgget(key,IPC_CREAT|0664);

    if (queue < 0)
    {
        perror("errore queue   \n ");
        exit(1);
    }
    
    return queue;
    
}


void invio(int queue,Messaggio M){

    int err;

    M.type_mex = 1;
    
    msgsnd(queue,(void *)&M,sizeof(Messaggio)-sizeof(long),0);

    M.type_mex = 2;

    msgsnd(queue,(void *)&M,sizeof(Messaggio)-sizeof(long),0);

    M.type_mex = 3;

    msgsnd(queue,(void *)&M,sizeof(Messaggio)-sizeof(long),0);
  
}


/*SEMAFORO MUTEX PER LA MUTUA ESCLUSIONE */


int init_sem(key_t key){

    int sem_id = semget(key,1,IPC_CREAT|0664);

    if (sem_id < 0)
    {
        perror("errore \n");
    }
    
    semctl(sem_id,MUTEX,SETVAL,1);

    return sem_id;

}

int Wait_sem(int sem_id,int num_sem){

    struct  sembuf p = {num_sem,-1,0};

    int err;

    err = semop(sem_id,&p,1);

    if (err < 0)
    {
        perror("wait error\n");
    }
    return err;
        
}

int Signal_sem(int sem_id,int num_sem){

    struct  sembuf p = {num_sem,1,0};

    int err;

    err = semop(sem_id,&p,1);

    if (err < 0)
    {
        perror("wait error\n");
    }
    return err;

}
