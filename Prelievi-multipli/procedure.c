#include"header.h"
#include"monitor.h"

#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

void Produttore(prod_cons_t *pc){

    enter_monitor(&(pc->M));

    if (pc->count == DIM)
    {

        wait_cond(&(pc->M),CV_PRODUTTORI);

    }
    
    
    pc->buff[pc->head] = getpid();
    
    pc->count++;
    
    pc->head = (pc->head + 1)%DIM;

    signal_cond(&(pc->M),CV_CONSUMATORI);

    leave_monitor(&(pc->M));

}

void Consumatore(prod_cons_t *pc){

    enter_monitor(&(pc->M));

    if (pc->count == 0 || pc->count < 2 )
    {
        wait_cond(&(pc->M),CV_CONSUMATORI);
    }


    printf("Consumatore primo valore %d\n",pc->buff[pc->tail]);

    pc->count--;

    pc->tail = (pc->tail + 1)% DIM;
    
    printf("Consumatore secondo valore %d\n",pc->buff[pc->tail]);

    pc->count--;

    pc->tail = (pc->tail + 1)% DIM;
    


    signal_cond(&(pc->M),CV_PRODUTTORI);

    leave_monitor(&(pc->M));

}
