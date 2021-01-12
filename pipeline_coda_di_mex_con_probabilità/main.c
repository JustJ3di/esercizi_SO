#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

 #include "header.h"

 int main(){

    int queue_client = msgget(IPC_PRIVATE,IPC_CREAT|0664);
    int queue_iniettore = msgget(IPC_CREAT,IPC_CREAT|0664);



    for (size_t i = 0; i < 3; i++)
    {
        pid_t pid = fork();

        Messaggio msg;

        if (pid == 0)
        {
            
            if (i == 0)
            {
                printf("invio  \n");

                strcpy(msg.string,"CLIENT1");
                msg.type_mex =strlen(msg.string);
                msgsnd(queue_client,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);
                exit(1);


            }
            else if (i == 1)
            {
                printf("invio  \n");

                strcpy(msg.string,"CLIENT2");
                msg.type_mex = strlen(msg.string);
                msgsnd(queue_client,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);

                exit(1);

            
            }
            else if (i == 2)
            {
                printf("invio  \n");

                strcpy(msg.string,"CLIENT3");
                msg.type_mex = strlen(msg.string);
                msgsnd(queue_client,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);

                exit(1);

            }
        
            

        }
        

    }


    pid_t pid = fork();

    if (pid == 0)
    {
    
        srand(getpid());



        for(int i = 0;i < 3;i++){

            int prob = rand()%99;

            printf("caso prob %d\n",prob);

            if (prob >= 0 && prob < 70)
            {
            
                Messaggio msg;

                printf("oele  1  \n");

                msgrcv(queue_client,(void *)&msg,sizeof(Messaggio)-sizeof(long),0,0);

                msgsnd(queue_iniettore,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);
                
            }
            
            else if (prob >= 70  && prob <80)
            {
            
                Messaggio msg;
                printf("oele   2 \n");
                msgrcv(queue_client,(void *)&msg,sizeof(Messaggio)-sizeof(long),0,0);

                int val = rand()%80;

                msg.type_mex = val;

                msgsnd(queue_iniettore,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);
                


            }

            else if (prob >= 80 && prob <100)
            {
            
                Messaggio msg,mex;
                printf("oele 3   \n");
                msgrcv(queue_client,(void *)&msg,sizeof(Messaggio)-sizeof(long),0,0);

                int val = rand()%64;
                mex.type_mex = val;

                strncpy(mex.string,msg.string,val);


                msgsnd(queue_iniettore,(void *)&mex,sizeof(Messaggio)-sizeof(long),0);
                

            }
            
        }    
        exit(1);

    }
    


    pid = fork();
    
    if (pid == 0)
    {
        for (size_t i = 0; i < 3; i++)
        {
            Messaggio msg;
            msgrcv(queue_iniettore,(void *)&msg,sizeof(Messaggio)-sizeof(long),0,0);

            if (msg.type_mex != 7 )
            {
                printf("errore  \n");
            }else
            {
                printf("%s\n",msg.string);
            }
            
        }

        exit(1);
        
    }
    
    for (size_t i = 0; i < 5; i++)
    {
        wait(NULL);
    }


    msgctl(queue_client,IPC_RMID,0);
    msgctl(queue_iniettore,IPC_RMID,0);
    

     return 0;
 }
