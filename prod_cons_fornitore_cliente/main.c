#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>

#include"header.h"

int main(){

    pid_t pid;

    int shm_id = shmget(IPC_PRIVATE,sizeof(Magazzino_t),IPC_CREAT|0664);

    if (shm_id < 0)
    {
        perror("error       \n");
    }


    Magazzino_t *m = (Magazzino_t *)shmat(shm_id,NULL,0);

    init_monitor(&(m->m),2);

    m->numero_liberi = 0;
    m->livello_scorte = DIM;

    for (size_t i = 0; i < DIM; i++)
    {
        m->scaff[i].stato = LIBERO;
    }


    for (size_t i = 0; i < 10; i++)
    {
        pid = fork();

            if (pid == 0)
            {
                
                for (size_t i = 0; i < 15; i++)
                {
                    Fornitore(m);
                }

                exit(2);

            }
            
    }
        


    for (size_t i = 0; i < 10; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            
            for (size_t i = 0; i < 15; i++)
            {
                Cliente(m);
            }
            
            exit(2);

        }
        

    }
    
    for (size_t i = 0; i < 20; i++)
    {
        wait(NULL);
    }


    remove_monitor(&(m->m));

    shmctl(shm_id,IPC_RMID,0);

    return 0;


}
