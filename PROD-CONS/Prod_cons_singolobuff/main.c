#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/errno.h>

#include "prodcons.h"
#include "semafori.h"


int main(int argc,char *argv[]){

    key_t key = IPC_PRIVATE;

    int shm_id = shmget(key,sizeof(int),IPC_CREAT|0664);
    if (shm_id < 0)
    {
        perror("errore nella shared\n");
        return -1;
    }

    int *msg_buff = (int *)shmat(shm_id,NULL,0);   //buffer creato contenente un intero
 
    if(!msg_buff){return -1;}

    int id_sem = init_sem(key,2);

    int prod_pid = fork();

    if(prod_pid == 0){
        produttore(msg_buff,id_sem);
        exit(1);
    }
    


    //QUI IL FIGLIO PRODUTTORE FA IL SUO




    int cons_pid = fork();

        //QUI IL FIGLIO CONSUMATORE FA IL SUO 

    if (cons_pid == 0){
        consumatore(msg_buff,id_sem);
        exit(2);
    }
    

    for (size_t i = 0; i < 2; i++)
        wait((int *)0);
    
    


    shmctl(shm_id,IPC_RMID,0);
    semctl(id_sem,0,IPC_RMID);
    semctl(id_sem,1,IPC_RMID);


    return 0;

}