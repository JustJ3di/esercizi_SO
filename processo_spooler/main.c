#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/wait.h>

#include"header.h"

int main(){

    pid_t pid;

    int status;

    key_t key = IPC_PRIVATE;

    int coda_server_printer,coda_client_server;

    coda_client_server = msgget(key,IPC_CREAT|0664);
    if (coda_client_server < 0)
    {
        perror("error  \n");
        exit(2);
    }

    coda_server_printer = msgget(key,IPC_CREAT|0664);
    if (coda_server_printer < 0)
    {
        perror("error \n");
        exit(2);
    }


    for (size_t i = 0; i < N_CLIENT; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            sleep(1);
            
            client(coda_client_server,getpid());
        
            exit(123);
        
        }
        
    }
    

    for (size_t i = 0; i < N_CLIENT ; i++)
    {
        wait(&status);
        printf("Processocliente morto con status %d \n",status);
    }
    
    
    pid = fork();


    if (pid == 0)
    {
        server(coda_client_server,coda_server_printer);
        exit(1);
    }

    pid = fork();

    if (pid == 0)
    {
        sleep(1);
        printer(coda_server_printer);
        exit(1);
    }
    
    
    wait(NULL);
    wait(NULL);
    


    msgctl(coda_client_server,IPC_RMID,0);
    msgctl(coda_server_printer,IPC_RMID,0);
    

    return 0;

}
