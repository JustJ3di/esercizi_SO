#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void copia_richiesta(richiesta *dst,richiesta *src){

    dst->posizione = src->posizione;
    dst->processo =  src->processo;

}

void utente(Vettore_richieste *p,richiesta elemento){

    enter_monitor(&(p->M));

    if (p->count == 10)
    {
        wait_condition(&(p->M),CV_PROD);
    }

    copia_richiesta(&(p->vett[p->testa]),&elemento);

    p->testa = (p->testa + 1)%10;
    

    p->count++;

    signal_condition(&(p->M),CV_CONS);

    leave_monitor(&(p->M));

}

richiesta schedulatore(Vettore_richieste *p){

    richiesta elemento;

    enter_monitor(&(p->M));

    if (p->count == 0)
    {
        wait_condition(&(p->M),CV_CONS);
    }
    
    copia_richiesta(&elemento,&(p->vett[p->coda]));
    p->coda = (p->coda +1)%10;
    p->count--;

    signal_condition(&(p->M),CV_PROD);

    leave_monitor(&(p->M));

    return elemento;
}
