#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<time.h>


#include"header.h"

int main(){


    key_t key = ftok(K1_PATH,K2_PATH);

    srand(time(NULL)*getpid());

    int queue = init_queue(key);

    Messaggio M;
    
    int k = 0;

    for (size_t i = 0; i < MEX_CLIENT; i++)
    {
        long n = k+1;
        M.type_mex = n ;

        M.VAL1 = rand()&10;
        M.VAL2 = rand()%10;

        invio(queue,M);
        
    }
    

    return 0;
}
