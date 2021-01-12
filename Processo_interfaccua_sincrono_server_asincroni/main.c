#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include "header.h"

int main(){


    pid_t pid_c;
    pid_t pid_s;
    pid_t pid_i;
    
    init_service_queue();

    int queue_request = msgget(IPC_PRIVATE,IPC_CREAT|0664);
    int queue_server_1 = msgget(IPC_PRIVATE,IPC_CREAT|0664);  
    int queue_server_2 = msgget(IPC_PRIVATE,IPC_CREAT|0664);
    int queue_server_3 = msgget(IPC_PRIVATE,IPC_CREAT|0664);



    for (size_t i = 0; i < 5; i++)
    {
        pid_c = fork();

        if (pid_c == 0)
        {
            srand(getpid());
            Messaggio_t msg = {rand()%10,getpid()};

            client(queue_request,msg);
            exit(1);
        }
        

    }
    
    pid_i = fork();

    if (pid_i == 0)
    {
        interfaccia(queue_server_1,queue_server_2,queue_server_3,queue_request);
        exit(1);
    }
    



    pid_s = fork();

    if (pid_s == 0)
    {
        server_1(queue_server_1);
        exit(1);
    }
    
    pid_s = fork();

    if (pid_s == 0)
    {
        server_2(queue_server_2);
        exit(1);
    }

    pid_s = fork();

    if (pid_s == 0)
    {
        server_3(queue_server_3);
        exit(1);
    }
    
    
    for (size_t i = 0; i < 9; i++)
    {
        wait(NULL);
    }
    
    

    msgctl(queue_request,IPC_RMID,0);

    msgctl(queue_server_1,IPC_RMID,0);

    msgctl(queue_server_2,IPC_RMID,0);

    msgctl(queue_server_3,IPC_RMID,0);

    destroy_service_queue();
    


    return 0;

}
