#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>

#include "header.h"

int main(){

    key_t key =  ftok(K1_PATH,K2_PATH);

    int queue = init_queue(key);

    int shm_id = init_shm(key);

    int sem_id = init_sem(key);

    for (size_t i = 0; i < N_CLIENT ; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            execlp("/home/emanuele/ProgettiSO/Esercizio_msg_server_mutex/client","client",NULL);
        }
        

    }
    

    for (size_t i = 0; i < N_SERVER; i++)
    {
        pid_t  pid = fork();

        if (pid == 0)
        {
            sleep(1);
            execlp("/home/emanuele/ProgettiSO/Esercizio_msg_server_mutex/server","server",NULL);
        }
        
    }


    for (size_t i = 0; i < N_CLIENT + N_SERVER; i++)
    {
        wait(NULL);
    }
    
    




    msgctl(queue,IPC_RMID,0);
    shmctl(shm_id,IPC_RMID,0);
    semctl(sem_id,MUTEX,IPC_RMID);

    return 0;
}
