#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>   
#include <sys/msg.h>
#include <sys/wait.h>

#include"header.h"

int main(int argc,char *argv[]){


//code messaggi



    int queue_msg = msgget(IPC_PRIVATE,IPC_CREAT|0664);

    int queue_tok = msgget(IPC_PRIVATE,IPC_CREAT|0664);

    Messaggio_t msg;

    for (size_t i = 0; i < 10; i++)
    {
        Messaggio_t msg;
        
        msg.tipo_mex = TOKEN;
        msg.val = 0;

        printf("invio il token n %ld\n",i);

        msgsnd(queue_tok,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0);
    
        
    
    }
    


//processi

    pid_t pid_prod,pid_cons;

    for (size_t i = 0; i < 4; i++)
    {

        pid_prod = fork();

        if (pid_prod == 0)
        {

//PRODUTTORE

            for (size_t k = 0; k < 5; k++)
            {

                Messaggio_t msg_tok;

                
                msgrcv(queue_tok,(void *)&msg_tok,sizeof(Messaggio_t)-sizeof(long),TOKEN,0);


                Messaggio_t msg;
                msg.tipo_mex = 1;
                msg.val = rand()%5+1;


                msgsnd(queue_msg,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),0);



            }

        exit(1);


        }
        

    }
     


    for (size_t i = 0; i < 2; i++)
    {
        
        pid_cons = fork();

        if (pid_cons == 0)
        {
            
//consumatore            
            for (size_t k = 0; k < 10; k++)
            {

                Messaggio_t msg;
                
                
                msgrcv(queue_msg,(void *)&msg,sizeof(Messaggio_t)-sizeof(long),1,0);

                sleep(1);

                printf("<%ld>messaggio <%d> consumato <%d>  \n",k,getpid(),msg.val);

                Messaggio_t msg_tok;

                msg_tok.tipo_mex = TOKEN;
                msg_tok.val = 0;

                msgsnd(queue_tok,(void *)&msg_tok,sizeof(Messaggio_t)-sizeof(long),0);


            

            }

            exit(1);            
            
        }
        

    }
    
    for (size_t i = 0; i < 6; i++)
    {
        wait(NULL);
    }
    
    msgctl(queue_msg,IPC_RMID,0);
    msgctl(queue_tok,IPC_RMID,0);


    return 0;
}