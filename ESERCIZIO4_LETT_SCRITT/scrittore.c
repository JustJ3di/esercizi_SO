#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<time.h>
#include<unistd.h>

#include"semafori.h"
#include"header.h"

int main(){

    buffer_t *pbuff;

    key_t key = ftok(PATH_KEY,PATH_CHAR);

    pid_t pid;
    
        printf("...SCRIVO....\n");
        sleep(1);

    int shm_id = shmget(key,sizeof(buffer_t),IPC_CREAT|0664);

    if (shm_id<0)
    {
        return -1;
    }
     
    pbuff = (buffer_t *)shmat(shm_id,NULL,0);

    int sem_id = init_sem(key,SIZE_SEM);

    srand(getpid()*time(NULL));


    Wait_sem(sem_id,SYNC);  //inizio scrittura

        pbuff->val1 = rand()%10;
        pbuff->val2 = rand()%10;

    Signal_sem(sem_id,SYNC); //fine scrittura

   
    return 0;

}