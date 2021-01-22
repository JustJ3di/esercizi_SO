#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<time.h>

#include"header.h"

int main(){

    key_t key = ftok(PATH1,PATH2);
//memoria
    int shm_id = init_shm(key);

    posto *buffer = shmat(shm_id,NULL,0);

//setting memoria

    for (size_t i = 0; i < POSTI_TOTALI; i++)
    {
        buffer->disp = POSTI_TOTALI;
        buffer->stato[i] = LIBERO;
    }
    

//semafori
    int sem_id = init_sem(key);

    semctl(sem_id,MUTEX_PROD,SETVAL,1);

//processo cliente

    pid_t pid;

    srand(time(NULL));

    for (size_t i = 0; i < 50; i++)
    {
        pid = fork();

        if (pid == 0)
        {

            sleep(1);
            cliente(sem_id,buffer);
            
            

        
            exit(2);
        
        
        }
        

    }
    

    for (size_t i = 0; i < 50; i++)
    {
        wait(NULL);
    }
    


    
//dealloca semafori 

    semctl(sem_id,MUTEX_PROD,IPC_RMID,0);

    return 0;

}