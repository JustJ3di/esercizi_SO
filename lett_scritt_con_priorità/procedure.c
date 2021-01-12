#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>


#include"header.h"

void Scrittori_high(Monitor_ls *ls){

    enter_monitor(&(ls->M));

    while (ls->num_lett > 0 || ls->num_scritt > 0)
    {

        wait_condition(&(ls->M),CV_SCRITTORI_HIGH_PRIORITY);    

    }


    ls->num_scritt++;

    leave_monitor(&(ls->M));

    sleep(1);

    srand(getpid());
    ls->buffer = rand()%10;
    printf("scrittore veloce %d\n",ls->buffer);
    
    enter_monitor(&(ls->M));

    ls->num_scritt--;

    if(queue_condition(&(ls->M),CV_SCRITTORI_HIGH_PRIORITY) > 0){

        signal_condition(&(ls->M),CV_SCRITTORI_HIGH_PRIORITY);

    }
    else if(queue_condition(&(ls->M),CV_LETTORI) > 0) {
     
        signal_all(&(ls->M),CV_LETTORI);
    }else{

        signal_condition(&(ls->M),CV_SCRITTORI_LOW_PRIORITY);

    }

    leave_monitor(&(ls->M));

}

void Scrittori_low(Monitor_ls *ls){


    enter_monitor(&(ls->M));

    while (ls->num_lett > 0 || ls->num_scritt > 0)
    {
        wait_condition(&(ls->M),CV_SCRITTORI_LOW_PRIORITY);

    }

    ls->num_scritt++;

    leave_monitor(&(ls->M));

    sleep(2);

    srand(getpid());
    ls->buffer = rand()%10;
    printf("SCRITTA LENTA = %d \n",ls->buffer);
    
    enter_monitor(&(ls->M));

    ls->num_scritt--;

    if(queue_condition(&(ls->M),CV_SCRITTORI_HIGH_PRIORITY) > 0)
    {
        signal_condition(&(ls->M),CV_SCRITTORI_HIGH_PRIORITY);

    }else if(queue_condition(&(ls->M),CV_LETTORI) > 0) {
     
        signal_all(&(ls->M),CV_LETTORI);
        
    }else{

        signal_condition(&(ls->M),CV_SCRITTORI_LOW_PRIORITY);
    }

    leave_monitor(&(ls->M));
}


void Lettori(Monitor_ls *ls){

    enter_monitor(&(ls->M));

    while(ls->num_scritt > 0){


        wait_condition(&(ls->M),CV_LETTORI);

    }

    ls->num_lett++;


    leave_monitor(&(ls->M));

    sleep(3);
    printf("valore letto %d\n",ls->buffer);

    enter_monitor(&(ls->M));


    ls->num_lett--;


    if(queue_condition(&(ls->M),CV_SCRITTORI_HIGH_PRIORITY) > 0 && ls->num_lett == 0){
        signal_condition(&(ls->M),CV_SCRITTORI_HIGH_PRIORITY);
    }else if(ls->num_lett == 0){
        signal_condition(&(ls->M),CV_SCRITTORI_LOW_PRIORITY);
    }

    leave_monitor(&(ls->M));

}
