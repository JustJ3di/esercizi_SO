#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>

#include"header.h"

void inserisci_operando(MonitorOperandi *mo,int operando){

    enter_monitor(&(mo->M));

    if (mo->count == 5)
    {
        wait_condition(&(mo->M),CV_PROD);
    }

    mo->operandi[mo->testa] = rand()%10 + 1;
    mo->testa = (mo->testa + 1)%5;
    mo->count++;

    signal_condition(&(mo->M),CV_CONS);

    leave_monitor(&(mo->M));

}
int *preleva_operando(MonitorOperandi *mo){

    static int operando[2];

    enter_monitor(&(mo->M));

    if (mo->count < 2)
    {
        wait_condition(&(mo->M),CV_CONS);
    }


    operando[0] = mo->operandi[mo->coda];
    mo->coda = (mo->coda +1)%5; 
   
    

    operando[1] = mo->operandi[mo->coda];
    mo->coda = (mo->coda +1)%5; 

    mo->count = mo->count-2;

 

        signal_condition(&(mo->M),CV_PROD);
        leave_monitor(&(mo->M));

  

    return operando;

}
void inserisci_risultato(MonitorRisultati * mr,int risultati){

    enter_monitor(&(mr->M));



    if (mr->liberi == 0)
    {
        wait_condition(&(mr->M),CV_PROD);
    }
    
    int i  = 0;
    while (i<=5 && mr->stato[i] !=LIBERO )
    {
        i++;
    }
    mr->stato[i] = IN_USO;
    mr->liberi--;
    
    leave_monitor(&(mr->M));

    mr->risultati[i] = risultati;
    
    enter_monitor(&(mr->M));

    mr->occupati++;
    mr->stato[i] = OCCUPATO;

    signal_condition(&(mr->M),CV_CONS);

    leave_monitor(&(mr->M));

}
int preleva_risultato( MonitorRisultati *mr){

    enter_monitor(&(mr->M));

    if (mr->occupati == 0)
    {
        wait_condition(&(mr->M),CV_CONS);
    }
    
    int i = 0;

    while (i<= 5 && mr->stato[i] != OCCUPATO)
    {
        i++;
    }
    mr->stato[i] = IN_USO;

    mr->occupati--;


    leave_monitor(&(mr->M));

    int risultato = mr->risultati[i];

    enter_monitor(&(mr->M));

    mr->stato[i] = LIBERO;
    mr->liberi++;

    signal_condition(&(mr->M),CV_PROD);
    leave_monitor(&(mr->M));

    return risultato;

}