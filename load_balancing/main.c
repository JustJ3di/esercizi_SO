#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/wait.h>

#include"header.h"

int main(){

    key_t key = IPC_PRIVATE;

    int queue_server[NUM_SERVER];
    int queue_client;

    for (size_t i = 0; i < NUM_SERVER; i++)
    {
        queue_server[i] = msgget(key,IPC_CREAT|0664);
    }

    queue_client = msgget(key,IPC_CREAT|0664);

    
    for (size_t i = 0; i < NUM_CLIENT; i++)
    {
        pid_t pid = fork();
//client
        if (pid == 0)
        {

            for (size_t i = 0; i < 15; i++)
            {
         
                Messaggio msg = {getpid(),getpid()};
                msgsnd(queue_client,(void *)&msg,SIZEOF(msg),0);
                sleep(1);
            }
            

        }
        

    }


    pid_t pid_bal = fork();

    if (pid_bal == 0)
    {
//balancer        
        int j = 0;
        Messaggio msg;
        for (size_t i = 0; i < NUM_CLIENT*15; i++)
        {
            msgrcv(queue_client,(void *)&msg,SIZEOF(msg),0,0);
            msgsnd(queue_server[j],(void *)&msg,SIZEOF(msg),0);
            j = (j+1)%NUM_SERVER;
        }
        
    }
    
    
    for (size_t i = 0; i < 3; i++)
    {
        pid_t pid = fork();
//server
        if (pid == 0)
        {
            Messaggio msg;

            for (size_t i = 0; i < ((NUM_CLIENT*15)/NUM_SERVER); i++)
            {
                
                msgrcv(queue_server[i],(void *)&msg,SIZEOF(msg),0,0);

                printf("server [i] contenuto <%d>\n",msg.contenuto);

            }
            
        }
        

    }
    

    for (size_t i = 0; i < 8+1+3; i++)
    {
        wait(NULL);
    }
    
    msgctl(queue_client,IPC_RMID,0);

    for (size_t i = 0; i < 3; i++)
    {
        msgctl(queue_server[i],IPC_RMID,0);
    }
    

    return 0;
}
