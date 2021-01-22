#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>


#include"header.h"

int main(){

    key_t key = ftok(PATH1,PATH2);

//memoria
    int shm_id = init_shm(key);

    posto *buffer = shmat(shm_id,NULL,0);

//semafori
    int sem_id = init_sem(key);

    semctl(sem_id,MUTEX_CONS,SETVAL,1);

    for(size_t i = 0;i<50;i++){

        int k = 0;

        Wait_sem(sem_id,MESSAGGIO_DISP);


        Wait_sem(sem_id,MUTEX_CONS);


        while(k <= POSTI_TOTALI && buffer->stato[k] !=OCCUPATO){

            k++;
            buffer->disp--;

        }

        if(buffer->disp  <= 0)
            printf("fine disponibilità\n");
        else 
            printf("disponibilità %d  \n",buffer->disp);
        

        buffer->stato[k] = IN_USO;


        Signal_sem(sem_id,MUTEX_CONS);


        sleep(1);
        

        printf("stato-- %d | id_utente-- %d | | \n",buffer->stato[k],buffer->id_utente[k]);
        
        buffer->stato[k] =  LIBERO;


        Signal_sem(sem_id,SPAZIO_DISP);

    }

    semctl(sem_id,MUTEX_CONS,IPC_RMID,0);
    semctl(sem_id,SPAZIO_DISP,IPC_RMID,0);
    semctl(sem_id,MESSAGGIO_DISP,IPC_RMID,0);

    shm_destroy(shm_id);

    return 0;

}