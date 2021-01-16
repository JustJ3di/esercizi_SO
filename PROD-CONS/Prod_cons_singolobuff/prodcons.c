#include "prodcons.h"
#include "semafori.h"


void produttore(int *msg_buff,int id_sem){

    sem_wait(id_sem,SPA_DISP);
    
    *msg_buff = 10;  //scrivo sul buff
    printf("Il produttore ha prodotto\n");
    
    sem_signal(id_sem,MSG_DISP);

}


void consumatore(int *msg_buff,int id_sem){

    int x;
    
    sem_wait(id_sem,MSG_DISP);
    x = *msg_buff;
    printf("il msg consumato ....:= %d\n",x);
    *msg_buff = 0;
    printf("Ora il il buff è  %d\n",*msg_buff);
    sleep(3);

    sem_signal(id_sem,SPA_DISP);

}