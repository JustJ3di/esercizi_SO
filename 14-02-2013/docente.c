#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/sem.h>
#include "header.h"
int main(){


    int shm_id = shmget(ftok(PATH1,PATH2),sizeof(esami),IPC_CREAT|0664);

    esami *p = (esami *)shmat(shm_id,NULL,0);

    int sem_id = init_sem(ftok(PATH1,PATH2),2);

    aggiorna_data("10/12/2018",p,sem_id);

    sleep(3);

    aggiorna_data("12/11/2018",p,sem_id);

    sleep(3);

    aggiorna_data("23/9/2018",p,sem_id);




    return 0;
}