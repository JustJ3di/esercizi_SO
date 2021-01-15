#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/msg.h>

#include"header.h"

int main(){

    int queue= msgget(ftok(PATH1,'a'),IPC_CREAT|0664);
    int queue_ok= msgget(ftok(PATH1,'b'),IPC_CREAT|0664);
    int queue_r= msgget(ftok(PATH1,'c'),IPC_CREAT|0664);

    for (size_t i = 0; i < 3; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            execl("./client","client",NULL);
        }
        
    }
    
    pid_t pid = fork();

    if (pid == 0)
    {
        execl("./server","server",NULL);
    }

    for (size_t i = 0; i < 4; i++)
    {
        wait(NULL);
    }
    
    msgctl(queue,IPC_RMID,0);
    msgctl(queue_ok,IPC_RMID,0);
    msgctl(queue_r,IPC_RMID,0);

    return 0;
}
