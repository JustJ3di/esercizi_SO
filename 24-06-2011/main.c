#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/wait.h>

#include"header.h"

int main(){

    int shm_id = shmget(IPC_PRIVATE,sizeof(Vettore_richieste),IPC_CREAT|0664);

    Vettore_richieste *v = shmat(shm_id,NULL,0);

    init_monitor(&(v->M),2);

    v->count = 0;
    v->coda = 0;
    v->testa = 0;
    

    for (size_t i = 0; i < 5; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            
            for (size_t i = 0; i < 5; i++)
            {
                srand(getpid());


                printf("richiesta   utente  \n");
                richiesta elemento = {rand()%20,getpid()};
                utente(v,elemento);
                sleep(1);
            }
            
            exit(1);
        }
        

    }
    
    pid_t pid = fork();

    if (pid == 0)
    {
        int j = 0;
    
        for (size_t i = 0; i < 25; i++)
        {
            int t = i;
            
            richiesta e[20];
            e[j] = schedulatore(v);
            printf("[SCHEDULER]  posizione <%d> |richiesta <%d>\n",e[j].posizione,e[j].processo);
            
            
            sleep(e[j].posizione);
            j = (j+1)%20;
        
        }

        exit(1);
    
    }

    for (size_t i = 0; i < 6; i++)
    {
        wait(NULL);
    }

    remove_monitor(&(v->M));

    shmctl(shm_id,IPC_RMID,0);
    

    return 0;
}