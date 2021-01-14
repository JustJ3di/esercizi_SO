#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<errno.h>
#include<unistd.h>

#include "semafori.h"
#include "lett_scrit.h"

void libera_tutti(int sem_id,int shm_id){

    shmctl(shm_id,IPC_RMID,0);
    semctl(sem_id,MUTEX,IPC_RMID);
    semctl(sem_id,SYNC,IPC_RMID);
    semctl(sem_id,MUTEXL,IPC_RMID);
    semctl(sem_id,MUTEXS,IPC_RMID);

}


int main(int argc,char *argv[]){


    key_t key = IPC_CREAT;
    lett_scrit_t *ps;
    pid_t pid;


    int shm_id = shmget(key,sizeof(lett_scrit_t),IPC_CREAT|0664);

    if (shm_id <0){perror("memoria non disponibile");}

    ps =(lett_scrit_t *)shmat(shm_id,NULL,0);

    if (!ps)
    {
        perror("out of memory");
        exit(3);
    }
    

    //inizializza i semafori
    int sem_id = init_sem(key,4);

    ps->index_lett = 0;
    ps->index_scrit = 0;
    ps->msg = 0;


    for (int k=0; k<MAX_PROCESSI; k++) {

        pid=fork();

        if (pid == 0)  {                //processi figlio
            if ( (k%2) == 0) {
                printf("\nsono il figlio scrittore. Il mio pid %d \n", getpid());
                scrittori(ps, sem_id);	        
                        
            } else {	
                printf("\nsono il figlio lettore. Il mio pid %d\n", getpid());
                lettori(ps, sem_id);
            }
                exit(0);
           }


        }


    for (int  i = 0; i < MAX_LETTORI+1; i++)
    {
        wait((int *)0);
    }
    

    libera_tutti(sem_id,shm_id);

    return 0;
}