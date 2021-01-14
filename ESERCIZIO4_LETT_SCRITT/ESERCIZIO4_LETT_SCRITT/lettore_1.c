#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<time.h>
#include<unistd.h>


#include"semafori.h"
#include"header.h"


/*************primo lettore**********************/


int main(){

    buffer_t *pbuff;

    printf("leggo..............\n");

    sleep(2);

    key_t key = ftok(PATH_KEY,PATH_CHAR);

    int shm_id = shmget(key,sizeof(buffer_t),IPC_CREAT|0664);

    if (shm_id<0)
    {
        return -1;
    }
     
    pbuff = (buffer_t *)shmat(shm_id,NULL,0);

    int sem_id = init_sem(key,SIZE_SEM);


    Wait_sem(sem_id,MUTEXL);

    pbuff->num_lettori++;

    if(pbuff->num_lettori == 1)
        Wait_sem(sem_id,SYNC);

    Signal_sem(sem_id,MUTEXL);
 

    printf("valore 1 : %d\n",pbuff->val1);

    Wait_sem(sem_id,MUTEXL);

    pbuff->num_lettori--;

    if(pbuff->num_lettori == 0)
        Signal_sem(sem_id,SYNC);

    Signal_sem(sem_id,MUTEXL);
       

    return 0;
}