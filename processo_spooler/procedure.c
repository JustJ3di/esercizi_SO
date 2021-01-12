#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/wait.h>


#include"header.h"




void client(int coda_client_server,int pid){

    int err;

    for (size_t i = 0; i < MEX_CLIENT; i++)
    {

        Messaggio m;

        m.pid_client = pid;

        m.type = i;

        msgsnd(coda_client_server,(void*)&m,sizeof(Messaggio)-sizeof(long),0);

        if (err < 0)
        {
            perror("send error    \n");
            exit(1);
        }
        

    }
    

}

void server(int coda_client_server,int coda_server_printer){

    int buff[10];

    for (size_t i = 0; i < 10; i++)
    {
        buff[i] = 0;
    }
    

    int k = 0;

    for (size_t i = 0; i < MEX_CLIENT*N_CLIENT; i++)
    {
        
    
        Messaggio m;


        if( k < 10 )
        {
        
            msgrcv(coda_client_server,(void *)&m,sizeof(Messaggio)-sizeof(long),0,0);
        
            buff[k] = m.pid_client;
            
            Messaggio M;    
            M.pid_client = buff[k];
            M.type = k;


            msgsnd(coda_server_printer,(void*)&M,sizeof(Messaggio)-sizeof(long),0);

            k++;


        }else if(k == 10)
        {            
            k = 0;
        }
        

        
    }

}



void printer(int coda_server_printer){

    Messaggio m;

    for (int i = 0;i<N_CLIENT*MEX_CLIENT;i++)
    {
           
        msgrcv(coda_server_printer,(void *)&m,sizeof(Messaggio)-sizeof(long),0,IPC_NOWAIT);

        printf("Messaggio   :%d\n",m.pid_client);

    }
    

}
