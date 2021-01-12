#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>

#include"monitor.h"
#include"header.h"

int main(){

    pid_t pid;

    int shm_id;
    
    
    shm_id = shmget(IPC_PRIVATE,sizeof(prod_cons_t),IPC_CREAT|0664);

    if (shm_id < 0)
    {
        perror("error shm\n");
        exit(2);
    }
    
    prod_cons_t *pc = (prod_cons_t *)shmat(shm_id,NULL,0);

    pc->count = 0;
    pc->tail = pc->head = 0;

    init_monitor(&(pc->M),2);

    for (size_t i = 0; i < PRODUTTORI; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            for (size_t i = 0; i < 6; i++)
            {
                Produttore(pc);
            }

            exit(2);
            
        }
        
    }
    

    for (size_t i = 0; i < CONSUMATORI; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            for (size_t i = 0; i < 3; i++)
            {
                Consumatore(pc);
            }

            exit(2);
            
        }
        
    }
    
    
    
    for (size_t i = 0; i < PRODUTTORI + CONSUMATORI ;i++)
    {
        wait(NULL);
    }
    
    destroy_monitor(&(pc->M));

    shmctl(shm_id,IPC_RMID,0);

    
    return 0;

}
