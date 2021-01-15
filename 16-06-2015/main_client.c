#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/msg.h>

#include"header.h"

int main(){

    int queue = msgget(ftok(PATH1,'a'),IPC_CREAT|0664);
    int oks_queue  = msgget(ftok(PATH1,'b'),IPC_CREAT|0664);
    int rts_queue = msgget(ftok(PATH1,'c'),IPC_CREAT|0664);

    printf("<%d>\n",queue);    

    for (size_t i = 0; i < 4; i++)
    {
        srand(getpid());

        Messaggio m;
        m.msg = 1;
        m.type = REQUEST_TO_SEND;

        msgsnd(rts_queue,(void *)&m,sizeof(Messaggio)-sizeof(long),0);
        printf("request to send \n");

        msgrcv(oks_queue,(void *)&m,sizeof(Messaggio)-sizeof(long),OK_TO_SEND,0);
        printf("client..send    \n");

        Messaggio mex;

        mex.msg = rand()%11;
        mex.type = getpid();

        msgsnd(queue,(void *)&mex,sizeof(Messaggio)-sizeof(long),0);


    }



    
    return 0;


}
