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


    Wait_sem(sem_id,MUTEX);

    p->num_lettori++;

    if (p->num_lettori == 1)
    {
        Wait_sem(sem_id,SYNC);
    }
    
    Signal_sem(sem_id,MUTEX);


    printf("prenoto sulla data appello <%s>\n",p->data);


    Wait_sem(sem_id,MUTEX);

    p->num_lettori--;
    p->prenotati++;

    if (p->num_lettori == 0)
    {
        Signal_sem(sem_id,SYNC);
    }
    
    Signal_sem(sem_id,MUTEX);

 

    return 0;
}