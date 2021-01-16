#include "semafori.h"
#include "prodcons.h"

int init_sem(key_t key,int num_sem){

    int sem_id = semget(key,num_sem,IPC_CREAT|0664);

    if(sem_id < 0){exit(1);}

    semctl(sem_id,MSG_DISP,SETVAL,0);
    semctl(sem_id,SPA_DISP,SETVAL,DIM);  
    semctl(sem_id,MUTEX_C,SETVAL,1);
    semctl(sem_id,MUTEX_P,SETVAL,1);

    return sem_id;

}

int sem_wait(int sem_id,int num_sem){

    int err;
    
    struct sembuf p = {num_sem, -1, 0};          //a facc ro cazz
    
    err  = semop(sem_id,&p,1);
    
    if(err<0){exit(1);}
    
    return err;
}

int sem_signal(int sem_id,int num_sem){

    int err;
    
    struct sembuf p = {num_sem, 1, 0};          //a facc ro cazz
    
    err  = semop(sem_id,&p,1);
    
    if(err<0){exit(1);}
    
    return err;
}