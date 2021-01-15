#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<pthread.h>

#include"header.h"

void *server_1(void *p){

    proteggere_t *pc = (proteggere_t *)p;



    for (int  i = 0; i < 6; i++)
    {
        pthread_mutex_lock(&(pc->mutex));
            printf("thread_1        \n");
        
        Messaggio service,mex;

        
        msgrcv(pc->rts_queue,(void *)&service,sizeof(Messaggio)-sizeof(long),REQUEST_TO_SEND,0);

        service.type = OK_TO_SEND;
        printf("ok to send \n");

        msgsnd(pc->oks_queue,(void *)&service,sizeof(Messaggio)-sizeof(long),0);

        msgrcv(pc->queue,(void *)&mex,sizeof(Messaggio)-sizeof(long),0,0);
        printf("messaggio thread server 1  <%d>\n",mex.msg);
        pthread_mutex_unlock(&(pc->mutex));
    }

    pthread_exit(NULL);

}

void *server_2(void *p){
        
    proteggere_t *pc = (proteggere_t *)p;


    for (int  i = 0; i <6; i++)
    {
//pthread_mutex_lock(&(pc->mutex));
 
        Messaggio service,mex;
 

        printf("secondo \n");
        msgrcv(pc->rts_queue,(void *)&service,sizeof(Messaggio)-sizeof(long),REQUEST_TO_SEND,0);

        service.type = OK_TO_SEND;

        msgsnd(pc->oks_queue,(void *)&service,sizeof(Messaggio)-sizeof(long),0);

        msgrcv(pc->queue,(void *)&mex,sizeof(Messaggio)-sizeof(long),0,0);

        printf("messaggio thread_server_2    <%d>\n",mex.msg);
        //pthread_mutex_unlock(&(pc->mutex));

    }

    pthread_exit(NULL);
    
}   





int main(){

    pthread_t thread[2];
    pthread_attr_t attr;



    proteggere_t *p = (proteggere_t *)malloc(sizeof(proteggere_t));

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&(p->mutex),NULL);    

    p->queue = msgget(ftok(PATH1,'a'),IPC_CREAT|0664);
    p->oks_queue = msgget(ftok(PATH1,'b'),IPC_CREAT|0664);
    p->rts_queue = msgget(ftok(PATH1,'c'),IPC_CREAT|0664);

    printf("<%d>\n",p->queue);  

    pthread_create(&thread[0],&attr,server_1,(void *)p);
    printf("primo creato\n");

    pthread_create(&thread[1],&attr,server_2,(void *)p);    


    for (size_t i = 0; i < 2; i++)
    {
        pthread_join(thread[i],NULL);
    }
    
    pthread_mutex_destroy(&(p->mutex));
    pthread_attr_destroy(&attr);
    
    free(p);

    return 0;    
}
