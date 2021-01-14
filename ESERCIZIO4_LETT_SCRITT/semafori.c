#include "semafori.h"

int init_sem(key_t key,int size_sem){

    int sem_id;
    if(semget(key,SIZE_SEM,IPC_CREAT|0664)<0)
        exit(2);
    sem_id = semget(key,SIZE_SEM,IPC_CREAT|0664);

    semctl(sem_id,MUTEXL,SETVAL,1);
    semctl(sem_id,SYNC,SETVAL,1);

    return sem_id;
}


int Wait_sem(int sem_id,int num_sem){

    struct sembuf p = {num_sem,-1,0};

    if (semop(sem_id,&p,1)<0)
    {
        return -1;
    }
    return semop(sem_id,&p,1);
    
}


int Signal_sem(int sem_id,int num_sem){

    struct sembuf p = {num_sem,1,0};

    if (semop(sem_id,&p,1)<0)
    {
        return -1;
    }
    return semop(sem_id,&p,1);
    
}