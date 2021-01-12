#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"monitor.h"


static void wait_sem(int,int);
static void signal_sem(int,int);
static int queue_sem(int,int);

void init_monitor(Monitor *M,int num_var){

    

    M->mutex = semget(IPC_PRIVATE,1,IPC_CREAT|0664);

    semctl(M->mutex,0,SETVAL,1);

    M->urgent_sem = semget(IPC_PRIVATE,1,IPC_CREAT|0664);

    semctl(M->mutex,0,SETVAL,1);

    M->id_cond= semget(IPC_PRIVATE,num_var,IPC_CREAT|0664);

    for (size_t i = 0; i < num_var; i++)
    {
        semctl(M->urgent_sem,0,SETVAL,0);
    }
    
    M->id_shared = shmget(IPC_PRIVATE,(num_var +1 )*sizeof(int),IPC_CREAT|0664);
    
    M->cond_count = (int *)shmat(M->id_shared,0,0);

    M->num_var_cond = num_var;

    M->urgent_count = M->cond_count + M->num_var_cond;

    for (size_t i  = 0; i < num_var; i++)
    {
        (M->cond_count[i]) = 0;
    }

    *(M->urgent_count ) = 0;
    

}




//***utilità
void wait_sem(int sem_id,int num_sem){

    struct sembuf p = {num_sem,-1,0};

    semop(sem_id,&p,1);

}

void signal_sem(int sem_id,int num_sem){

    struct sembuf p = {num_sem,1,0};

    semop(sem_id,&p,1);
    
}


//*****enter monitor

void enter_monitor(Monitor *M){

    wait_sem(M->mutex,0);

}

//***leave monitor

void leave_monitor(Monitor *M){

    if (*(M->urgent_count)  > 0)
    {
        signal_sem(M->urgent_sem,0);
    
    }else{

        signal_sem(M->mutex,0);

    }
    

    signal_sem(M->mutex,0);

}


void destroy_monitor(Monitor *M){

    semctl(M->mutex,0,IPC_RMID,0);
    semctl(M->urgent_sem,0,IPC_RMID,0);
    semctl(M->id_cond,M->num_var_cond,IPC_RMID,0);
    shmctl(M->id_shared,IPC_RMID,0);


}

void wait_cond(Monitor *M,int id_var){

    M->cond_count[id_var] = M->cond_count[id_var]+1;

    if(*(M->urgent_count)>0){
        signal_sem(M->urgent_sem,0);
    }else{

        signal_sem(M->mutex,0);

    }

    wait_sem(M->id_cond,id_var);

    M->cond_count[id_var] = M->cond_count[id_var]-1;

    
}


void signal_cond(Monitor *M,int id_var){

    *(M->urgent_count) = *(M->urgent_count) + 1;

    if (M->cond_count[id_var] > 0)
    {
        signal_sem(M->id_cond,id_var);
    
        wait_sem(M->urgent_sem,0);

    }

    (*(M->urgent_count))--;
    
}

int queue_condition(Monitor * M,int id_var){
    return M->cond_count[id_var];
}

int queue_sem(int id_sem,int num_sem){

        return (semctl(id_sem,num_sem,GETNCNT,NULL));

}


