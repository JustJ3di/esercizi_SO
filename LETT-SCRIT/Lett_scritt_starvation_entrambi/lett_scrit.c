#include "lett_scrit.h"
#include "semafori.h"


void inizio_lettura(lett_scrit_t *ps,int sem_id){

    Wait_sem(sem_id,MUTEXL);
   
    ps->index_lett = ps->index_lett +1;
    if (ps->index_lett == 1){Wait_sem(sem_id,SYNC);}

    Signal_sem(sem_id,MUTEXL);
}

void fine_lettura(lett_scrit_t *ps,int sem_id){

    Wait_sem(sem_id,MUTEXL);
   
    ps->index_lett = ps->index_lett -1;
    if (ps->index_lett == 0){Signal_sem(sem_id,SYNC);}
   
    Signal_sem(sem_id,MUTEXL);

    
}

void inizio_scrittura(lett_scrit_t *ps,int sem_id){


    Wait_sem(sem_id,MUTEXS);
   
    ps->index_scrit = ps->index_scrit + 1;
    if (ps->index_scrit == 1){Wait_sem(sem_id,SYNC);}

    Signal_sem(sem_id,MUTEXS);

    Wait_sem(sem_id,MUTEX);

}

void fine_scrittura(lett_scrit_t *ps,int sem_id){

    
    Signal_sem(sem_id,MUTEX);

    Wait_sem(sem_id,MUTEXS);
   
    ps->index_scrit = ps->index_scrit - 1;
    if (ps->index_scrit == 0){Signal_sem(sem_id,SYNC);}

    Signal_sem(sem_id,MUTEXS);


}


void lettori(lett_scrit_t *ps,int sem_id){

    inizio_lettura(ps,sem_id);
    
    printf("\nIl Messaggio letto vale %d  \n  Numero lettore %d \n",ps->msg,ps->index_lett);

    fine_lettura(ps,sem_id);

}

void scrittori(lett_scrit_t *ps,int sem_id){

    inizio_scrittura(ps,sem_id);

    srand(getpid()*time(NULL));
    ps->msg = random()%100;
    printf("HO SCRITTO %d",ps->msg);

    fine_scrittura(ps,sem_id);

}