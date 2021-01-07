#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/errno.h>
#include "time.h"

#include "prodcons.h"
#include "semafori.h"


void dealloca_tutto(int shm_id,int id_sem){
    
    shmctl(shm_id,IPC_RMID,0);
    semctl(id_sem,MSG_DISP,IPC_RMID);
    semctl(id_sem,SPA_DISP,IPC_RMID);
    semctl(id_sem,MUTEX_C,IPC_RMID);
    semctl(id_sem,MUTEX_P,IPC_RMID);
}

int main(int argc,char *argv[]){

    key_t key = IPC_PRIVATE;
    int size = sizeof(prodcons_t);

    int shm_id = shmget(key,size,IPC_CREAT|0664);
    if (shm_id < 0)
    {
        perror("errore nella shared\n");
        return -1;
    }

    prodcons_t *ps = (prodcons_t *)shmat(shm_id,NULL,0);   //buffer creato contenente un intero
 
    if(!ps){return -1;}

    ps->coda = 0;
    ps->testa = 0;
    

    int id_sem = init_sem(key,4);


    for (size_t i = 0; i < NUM_PROD; i++)
    {
        int prod_pid = fork();

        if(prod_pid == 0){
            
            srand(getpid()*time(NULL));

            produttore(ps,id_sem);
            exit(1);
        }    
    }
    
    

    for (size_t i = 0; i < NUM_PROD; i++)
    {
        int cons_pid = fork();

        if(cons_pid == 0){
            consumatore(ps,id_sem);
        
            exit(1);
        }    
    }
    
    


    for (size_t i = 0; i < NUM_CONS+NUM_PROD; i++)
        wait((int *)0);
    
    
    dealloca_tutto(shm_id,id_sem);


    return 0;

}
