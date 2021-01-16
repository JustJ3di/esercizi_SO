#include "prodcons.h"
#include "semafori.h"

void produttore(prodcons_t *ps,int id_sem){


    int index = 0;    
    
    sem_wait(id_sem,SPA_DISP);
    sem_wait(id_sem,MUTEX_P);
    while(index<=DIM && ps->vett_stat[index]!=BUFFER_VUOTO) //cerco il primo indice dellvettore di stato libero
        index++;
    
    ps->vett_stat[index] = BUFFER_IN_USO;
  
    sem_signal(id_sem,MUTEX_P);

    //PRODUZIONE ORA STA FUORI LA REGIONE CRITICAAAA
    ps->buffer[index] = rand()%100;
   
    printf("valore prodotto %d\n",ps->buffer[index]);

    ps->vett_stat[index] = BUFFER_PIENO;
    
    sem_signal(id_sem,MSG_DISP);


}

void consumatore(prodcons_t *ps,int id_sem){

    int index = 0;    
    
    sem_wait(id_sem,MSG_DISP);
  
    sem_wait(id_sem,MUTEX_C);
  
    while(index<=DIM && ps->vett_stat[index]!=BUFFER_PIENO) //cerco il primo indice che punta ha un stato buffer pieno
        index++;
    
    ps->vett_stat[index] = BUFFER_IN_USO;
  
    sem_signal(id_sem,MUTEX_C);

    //CONSUMAZIONE FUORI DALLA ZONA CRITICAAA

    printf("valore consumato %d\n",ps->buffer[index]);

    ps->vett_stat[index] = BUFFER_VUOTO;
    
    sem_signal(id_sem,SPA_DISP);


}