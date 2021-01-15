#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/wait.h>

#include"header.h"

int main(){


    pid_t M_pid;
    pid_t utenti_pid;

    int shm_id = shmget(IPC_PRIVATE,sizeof(Meteo),IPC_CREAT|0664);

    Meteo *met = shmat(shm_id,NULL,0);    

    init_monitor(&(met->M),2);

    M_pid = fork();

    if (M_pid == 0)
    {
        for (size_t i = 0; i < 20; i++)
        {
            Scrittura(met);
            sleep(2);
        }
        exit(2);   
    }
        


    for (size_t i = 0; i < NUM_LETTORI; i++)
    {
    
        utenti_pid = fork();

        if (utenti_pid == 0)
        {
            for(int i = 0;i< 10 ;i++)
            {
                Lettura(met);
                sleep(1);
            }
            exit(2);
        }
        

    }
    

    for (size_t i = 0; i < 1 + NUM_LETTORI; i++)
    {
        wait(NULL);
    }
    

    
    remove_monitor(&(met->M));

    shmctl(shm_id,IPC_RMID,0);

    return 0;
}