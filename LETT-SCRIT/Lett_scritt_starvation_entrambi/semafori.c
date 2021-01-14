#include "semafori.h"

int init_sem(key_t key,int num_sem){

    int sem_id = semget(key,num_sem,IPC_CREAT|0664);

    if(sem_id<0){exit(2);}

    semctl(sem_id,MUTEX,SETVAL,1);
    semctl(sem_id,MUTEXL,SETVAL,1);
    semctl(sem_id,MUTEXS,SETVAL,1);
    semctl(sem_id,SYNC,SETVAL,1);

    return sem_id;

}

int Signal_sem(int sem_id,int sem_index){

    struct sembuf p = {sem_index,1,0};

    int err;

    err = semop(sem_id,&p,1);
    
    if (err < 0){exit(2);}
    
    return err;

}

int Wait_sem(int sem_id,int sem_index){

    struct sembuf p = {sem_index,-1,0};

    int err;

    err = semop(sem_id,&p,1);
    
    if (err < 0){exit(2);}
    
    return err;

}