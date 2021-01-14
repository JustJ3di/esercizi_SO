#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>

#include"semafori.h"
#include"header.h"

int main(){

    key_t key = ftok(PATH_KEY,PATH_CHAR);

    pid_t pid;

    int shm_id = shmget(key,sizeof(buffer_t),IPC_CREAT|0664);

    if (shm_id<0)
    {
        return -1;
    }

    buffer_t *pbuff = (buffer_t *)shmat(shm_id,NULL,0);

    pbuff->num_lettori = 0;
     
    int sem_id = init_sem(key,SIZE_SEM);

    for (size_t i = 0; i <  N_SCRITTORI; i++)
    {
        pid = fork();
        
        if (pid == 0){
        
            
                execlp("/home/emanuele/ProgettiSO/ESERCIZIO4_LETT_SCRITT/scrittore","scrittore",NULL);

        }

        
    }

    for (size_t i = 0; i < N_LETTORI; i++)
    {
        pid = fork();
        if (pid == 0)
        {
                execlp("/home/emanuele/ProgettiSO/ESERCIZIO4_LETT_SCRITT/lettore_1","lettore_1",NULL);
        }
        
    }
    

    for (size_t i = 0; i < N_LETTORI; i++)
    {
        pid = fork();
        if (pid == 0)
        {
        
        
            execlp("/home/emanuele/ProgettiSO/ESERCIZIO4_LETT_SCRITT/lettore_2","lettore_2",NULL);
    
    
        }
    }
    

    
    for (size_t i = 0; i <  N_LETTORI + N_LETTORI + N_SCRITTORI; i++)
    {
        wait(NULL);
    }
    

    shmctl(shm_id,IPC_RMID,0);
    semctl(sem_id,MUTEXL,IPC_RMID);
    semctl(sem_id,SYNC,IPC_RMID);       


    return 0;
}