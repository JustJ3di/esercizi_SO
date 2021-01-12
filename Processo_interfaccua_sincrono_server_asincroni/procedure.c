#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include "header.h"

//code di servizio

static int ok_send;  
static int request_send;


void init_service_queue(){

    ok_send = msgget(ftok(".",'a'),IPC_CREAT|0664);

    request_send = msgget(ftok(".",'a'),IPC_CREAT|0664);

}

void destroy_service_queue(){

    msgctl(ok_send,IPC_RMID,0);
    msgctl(request_send,IPC_RMID,0);


}


//client

void client(int request_queue,Messaggio_t msg){

    Messaggio_t msg_service;

    msg_service.tipo_mex = REQUEST_TO_SENT;

    printf("client\n");

    msgsnd(request_send,(void *)&msg_service,sizeof(Messaggio_t)-sizeof(long),0);

    msgrcv(ok_send,(void *)&msg_service,sizeof(Messaggio_t)-sizeof(long),OK_TO_SEND,0);

    printf("sincronia client\n");

    printf("il messaggio che il cliente invia <%ld> e <%d>\n",msg.tipo_mex,msg.val);

    for (size_t i = 0; i < 5; i++)
    {
        
        msgsnd(request_queue,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0);
        printf("invio messaggi all interface \n");

    }
    

}

//interfaccia


void interfaccia(int queue_server_1,int queue_server_2,int queue_server_3,int request_queue){

    Messaggio_t msg_service,msg;

    printf("interfaccia\n");

    int queue[3];
    queue[0] = queue_server_1;
    queue[1] = queue_server_2;
    queue[2] = queue_server_3;

    for (size_t i = 0; i < 5; i++)
    {
    
        msgrcv(request_send,(void *)&msg_service,sizeof(Messaggio_t)-sizeof(long),REQUEST_TO_SENT,0);

        msg_service.tipo_mex = OK_TO_SEND;

        msgsnd(ok_send,(void *)&msg_service,sizeof(Messaggio_t)-sizeof(long),0);

    }

    printf("sincronia interface\n");

    int j  = 0;
    for (size_t i = 0; i < 5*5; i++)
    {
        msgrcv(request_queue,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0,0);
        printf("messaggio ricevuto dall interface   \n");
        msgsnd(queue[j],(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0);
        j = (j+1)%3;
    }
    



}



//processi server

void server_1(int queue_server_1){

    Messaggio_t msg;

    for (size_t i = 0; i < 5; i++)
    {
        msgrcv(queue_server_1,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0,0);
        printf("SERVER 1 pid <%ld>  || messaggio <%d>\n",msg.tipo_mex,msg.val);
    }
    

}

void server_2(int queue_server_2){

    Messaggio_t msg;

    for (size_t i = 0; i < 5; i++)
    {
        msgrcv(queue_server_2,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0,0);
        printf("SERVER 2 pid <%ld>  || messaggio <%d>\n",msg.tipo_mex,msg.val);
    }
    

}

void server_3(int queue_server_3){

        Messaggio_t msg;

        for (size_t i = 0; i < 5 ; i++)
        {
            
            msgrcv(queue_server_3,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0,0);
            printf("SERVER 3 pid <%ld>  || messaggio <%d>\n",msg.tipo_mex,msg.val);

        }
}
