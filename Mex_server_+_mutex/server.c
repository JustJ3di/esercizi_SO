#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h> 
#include<sys/sem.h>
#include<time.h>

#include "header.h"

int main(){

    key_t key = ftok(K1_PATH,K2_PATH);

    int queue = init_queue(key);

    int sem_id = init_sem(key);

    int shm_id = init_shm(key);

    shared *ps = shmat(shm_id,NULL,0);

    Wait_sem(sem_id,MUTEX);

    int k = 0;
    Messaggio M;


    for (size_t i = 0; i < MEX_CLIENT*N_CLIENT; i++)
    {
            
            long n  = k+1;
            
            msgrcv(queue,(void *)&M,sizeof(Messaggio)-sizeof(long),n,0);

            ps->valore1 = M.VAL1;
            ps->valore2 = M.VAL2;

            printf("SERVER %ld \nVALORE 1 %d\nVALORE 2 %d\n\n",n,ps->valore1,ps->valore2); 

            k = (k+1)%3;

    }
    Signal_sem(sem_id,MUTEX);    

    return 0;
}
