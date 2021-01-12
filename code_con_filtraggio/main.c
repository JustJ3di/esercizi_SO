#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/wait.h>

#include"header.h"


int main(){

    key_t key = IPC_PRIVATE;

    pid_t pid;

    int queue[3];


    

    for (size_t i = 0; i < 3; i++)
    {
        queue[i] =crea_code(key);
    }
    
    for (size_t i = 0; i < 3; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            generatore(queue[0]);
            exit(1);
        }
        
    }

    for (size_t i = 0; i < 3; i++)
    {
        wait(NULL);
    }
    
    pid = fork();

    if (pid == 0)
    {
        filtro(queue[0],queue[1]);
        exit(2);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0)
    {
        checksum(queue[1],queue[2]);
        exit(1);
    }
    wait(NULL);

    pid = fork();

    if (pid == 0)
    {
        visualizzatore(queue[2]);
        exit(2);
    }
    wait(NULL);

    for (size_t i = 0; i < 3; i++)
    {
        msgctl(queue[i],IPC_RMID,0);
    }

     
    
    return 0;

}


