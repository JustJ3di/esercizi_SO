#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>


#include"header.h"

int main(){


    pid_t pid;

    int shm_id = shmget(IPC_PRIVATE,sizeof(Monitor_ls),IPC_CREAT|0664);
 
    Monitor_ls * ls = (Monitor_ls *)shmat(shm_id,NULL,0);


    init_monitor(&(ls->M),2);

    ls->num_lett = 0,
    ls->num_scritt = 0;
    ls->num_scrittore_high_prority = 0;
    ls->num_lettori_attesa = 0;

    for (size_t i = 0; i < N_LETTORI; i++)  // creo 3 processi
    {
        pid = fork();
        
        if (pid == 0){
            
            for(int i = 0;i < 3;i++){
                sleep(3);

                Lettori(ls);
            }

            exit(3);
   
        }
   
    }

    for (size_t i = 0; i < N_SCRITTORI_H; i++)
    {
        pid = fork();

        if (pid == 0){

            for(int i = 0;i<3;i++){
                sleep(3);

                Scrittori_high(ls);
            
            }

            exit(1);

        }
        
    }
    

    for (size_t i = 0; i < N_SCRITTORI_H; i++){


        pid = fork();

        if (pid == 0){

            for(int i = 0;i<3;i++){

            sleep(3);
            
            Scrittori_low(ls);
            
            }

            exit(3);

        }
        
    }
    
    
    for (size_t i = 0; i < N_LETTORI + N_SCRITTORI_H + N_SCRITTORI_L; i++){
        wait(NULL);
    }
    

    remove_monitor(&(ls->M));


    return 0;
}
