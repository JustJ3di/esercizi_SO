#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include "procedure.h"


int main(int argc ,char *argv[]){


    //allocare e inizizalizzare la shared memory
    
    key_t shmem= IPC_PRIVATE;

    int *p = NULL;

    pid_t shm_ds = shmget(shmem,sizeof(int),IPC_CREAT|0664);
    
    if(shm_ds < 0){
        perror("shm non creata");
        exit(1);
    }
    
    p = (int *)shmat(shm_ds,NULL,0);

    *p = 0;
    
    if(!p){
        perror("out of memory");
        exit(1);
    }
    
    printf("il valore del shm è %d \n",*p);

    //allocare e inizializzare i semafori
    
    
    key_t k_sem = IPC_PRIVATE;

    int id_sem = semget(k_sem,1,IPC_CREAT|0664);
    
    semctl(id_sem,0,SETVAL,1);

    printf("Sem %d inizializzato a 1\n",id_sem);
    
    //
    //generare i due processi
    int i;
    for (i = 0; i < 2; i++){

        pid_t cpid =fork();

        if (cpid < 0){
            perror("errore fork");
            exit(1);
        }
    
        else if(cpid == 0){

            for (int j = 0; j < 100; j++){
                
                wait_sem(id_sem,0);
                //SEZ_CRITICA
                printf("sono il figlio : %d ",getpid());
                
                printf("processo %d ha letto il valore\n",j);
                (*p)++;  //incremento il valore puntato da p;
                printf("processo %d ha incr.\n",j);
                //FINE SEZ_CRITICA
                signal_sem(id_sem,0);
            
            }
            exit(0);
        }
        
    }
    
    //wait sul figlio (figlio si ricongiungie al padre)

    for(int i = 0;i < 2;i++)
        wait((int *)0);

    //deallocare shared memory e semafori

    shmctl(shm_ds,IPC_RMID,0);
    semctl(id_sem,IPC_RMID,0);



    return 0;
}
