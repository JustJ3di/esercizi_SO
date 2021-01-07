#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"

static int coda_RTS;
static int coda_OTS;


void initServiceQueues(){

    /* TBD: inizializzazione code per implementare la send sincrona */
    coda_RTS = msgget(IPC_PRIVATE,IPC_CREAT|0664);/* TBD */
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = msgget(IPC_PRIVATE,IPC_CREAT|0664);  /* TBD */
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

void removeServiceQueues(){
    /* TBD: rimozione code per implementare la send sincrona */

    msgctl(coda_OTS,IPC_RMID,0);
    msgctl(coda_RTS,IPC_RMID,0);

}


void controllore(int ds_queue_control_proxy){
    
    /*TBD: Definire le variabili necessarie */
    Volo x;
    Control y = {RTS_SEND,1};

    srand(getpid());    

    int i;
    for (i=0; i<10; i++){
        
        /* TBD: Implementare lo scambio di messaggi necessario per
         * avere una send sincrona */
        msgsnd(coda_RTS,(void *)&y,sizeof(Control)-sizeof(long),0);

        msgrcv(OKS_SEND,(void *)&y,sizeof(Control)-sizeof(long),OKS_SEND,0);
        
        if (i%2 == 0){
            
            /* TBD: Implementare invio messaggi per voli in ARRIVO */
            strcpy(x.citta_arrivo,"Napoli");
            strcpy(x.citta_partenza,"Milano");
            strcpy(x.direzione,"partenza");
            x.ID  = rand()%11;
            x.tipo = PARTENZE;

            msgsnd(ds_queue_control_proxy,(void *)&x,sizeof(Volo)-sizeof(long),0);

        }else {

            /* TBD: Implementare invio messaggi per voli in PARTENZA */
            strcpy(x.citta_arrivo,"Roma");
            strcpy(x.citta_partenza,"Torino");
            strcpy(x.direzione,"arrivo");
            x.ID  =rand()%11;
            x.tipo = ARRIVI;

            msgsnd(ds_queue_control_proxy,(void *)&x,sizeof(Volo)-sizeof(long),0);
        }
        
    }
    exit(0);
    
}
void proxy(int ds_queue_control_proxy, int ds_queue_proxy_gestori){
    
    int i, ret;
    Volo v;
    for (i=0; i<10; i++){
        
        /* TBD: Implementare lo scambio di messaggi necessario per
         * avere una send sincrona */
        Control x;
        msgrcv(coda_RTS,(void *)&x,sizeof(Control)-sizeof(long),RTS_SEND,0);

        x.tipo = OKS_SEND;
        x.value = 1;

        msgsnd(coda_OTS,(void *)&x,sizeof(Control)-sizeof(long),0);

        /* TBD: Aggiungere la ricezione del volo vero e proprio */
        Volo msg;

        msgrcv(ds_queue_control_proxy,(void *)&msg,sizeof(Volo)-sizeof(long),0,0);

        /* TBD: Aggiungere il codice per inviare opportunamente il volo
         * ricevuto al Gestore Arrivi o al Gestore Partenze
         */
        if (strcmp(msg.direzione,"partenza")== 0)
        {
            msgsnd(ds_queue_proxy_gestori,(void *)&msg,sizeof(Volo)-sizeof(long),0);
            sleep(1);
        }else
        {
            msgsnd(ds_queue_proxy_gestori,(void *)&msg,sizeof(Volo)-sizeof(long),0);
            sleep(1);
        }
        
        

    }
    exit(0);
}

void stampa_volo_info(Volo *v){
    
    printf("STAMPO INFO VOLO\n");
    printf("..........................ID: %d\n", v->ID);
    printf("..........................direzione: %s\n", v->direzione);
    printf("..........................citta_partenza: %s\n", v->citta_partenza);
    printf("..........................citta_arrivo: %s\n", v->citta_arrivo);
    
}

void gestore_arrivi(int ds_queue_proxy_gestori){
    
    int ret, i;
    Volo v;
    
    for (i=0; i<5; i++){
        
        /* TBD: Ricezione voli in ARRIVO */
        msgrcv(ds_queue_proxy_gestori,(void *)&v,sizeof(Volo)-sizeof(long),ARRIVI,0);
        
        printf("\n\n****** ARRIVI ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

void gestore_partenze(int ds_queue_proxy_gestori){
    
    int ret, i;
    Volo v;
    for (i=0; i<5; i++){
        
        /* TBD: Ricezione voli in PARTENZA */
        msgrcv(ds_queue_proxy_gestori,(void *)&v,sizeof(Volo)-sizeof(long),PARTENZE,0); 
        printf("\n\n****** PARTENZE ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

