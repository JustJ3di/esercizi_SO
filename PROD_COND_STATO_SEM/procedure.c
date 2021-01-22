
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h> 


#include"header.h"

//semafori


int init_sem(key_t key){

    
    int sem_id = semget(key,4,IPC_CREAT|0664);

    if (sem_id < 0)
    {
        perror("error\n");
        exit(1);
    }

    semctl(sem_id,SPAZIO_DISP,SETVAL,POSTI_TOTALI);
    semctl(sem_id,MESSAGGIO_DISP,SETVAL,0);

    return sem_id;
    
    
}



void Wait_sem(int sem_id,int num_sem){

    struct sembuf p ={num_sem,-1,0};

    semop(sem_id,&p,1); 

}




void Signal_sem(int sem_id,int num_sem){

    struct sembuf p = {num_sem,1,0};

    semop(sem_id,&p,1);

}



//shared_memory
int init_shm(key_t key){

    int shm_id = shmget(key,sizeof(posto),IPC_CREAT|0664);

    if (shm_id < 0)
    {
        perror("error \n");
        exit(1);
    }
    

    return shm_id;

}


void shm_destroy(int shm_id){

    shmctl(shm_id,IPC_RMID,0);

}

//procedura clienti

void cliente(int sem_id,posto *buffer){

    srand(getpid());


    for(int k = 1;k<(rand()%4+1) ;k++){
    
        int i = 0;



        Wait_sem(sem_id,SPAZIO_DISP);

        
        Wait_sem(sem_id,MUTEX_PROD);


        
        while(i <= POSTI_TOTALI  && buffer->stato[i] != LIBERO){
        
            i++;
        
        }
        
        
        buffer->stato[i] = IN_USO;

        //buffer->disp--;

            

        Signal_sem(sem_id,MUTEX_PROD);

        sleep(rand()%2+1);

        buffer->id_utente[i] = getpid();


        buffer->stato[i] = OCCUPATO;

        printf("utende-id <%d> prenotazione n <%d>\n",buffer->id_utente[i],k);

        
        Signal_sem(sem_id,MESSAGGIO_DISP);    


    }

}