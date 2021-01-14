#include "lett_scrit.h"
#include "semafori.h"


void inizio_lettura(lett_scrit_t *ps,int sem_id){

    Wait_sem(sem_id,MUTEX);
   
    ps->index_lett = ps->index_lett +1;
    if (ps->index_lett == 1){Wait_sem(sem_id,SYNC);}

    Signal_sem(sem_id,MUTEX);
}

void fine_lettura(lett_scrit_t *ps,int sem_id){

    Wait_sem(sem_id,MUTEX);
   
    ps->index_lett = ps->index_lett -1;
    if (ps->index_lett == 0){Signal_sem(sem_id,SYNC);}
   
    Signal_sem(sem_id,MUTEX);
    
}

void inizio_scrittura(lett_scrit_t *ps,int sem_id){


    Wait_sem(sem_id,SYNC);

}

void fine_scrittura(lett_scrit_t *ps,int sem_id){

    Signal_sem(sem_id,SYNC);

}


void lettori(lett_scrit_t *ps,int sem_id){

    inizio_lettura(ps,sem_id);
    
    printf("Il Messaggio letto vale %d    Numero lettore %d \n",ps->msg,ps->index_lett);

    fine_lettura(ps,sem_id);

}

void scrittori(lett_scrit_t *ps,int sem_id){

    inizio_scrittura(ps,sem_id);

    srand(getpid()*time(NULL));
    printf("scrivo....\n");
    ps->msg = random()%100;

    fine_scrittura(ps,sem_id);

}