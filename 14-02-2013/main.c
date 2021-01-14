#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>

#include"header.h"

int main(){

    int shm_id = shmget(ftok(PATH1,PATH2),sizeof(esami),IPC_CREAT|0664);

    esami *p = (esami *)shmat(shm_id,NULL,0);

    int sem_id = init_sem(ftok(PATH1,PATH2),2);

    p->prenotati = 0;
    p->num_lettori = 0;

    semctl(sem_id,MUTEX,SETVAL,1);
    semctl(sem_id,SYNC,SETVAL,1);

    for (size_t i = 0; i < 10; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            srand(getpid());
            sleep(rand()%9);
            execl("./studente","studente",NULL);
            

        }
        

    }
    
    pid_t pid = fork();

    if (pid == 0)
    {
        execl("./docente","docente",NULL);
    }
    
    for (size_t i = 0; i < 11; i++)
    {
        wait(NULL);
    }


    shmctl(shm_id,IPC_RMID,NULL);


    destroy_sem(sem_id,2);


    return 0;    

}
