#include"header.h"

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void Fornitore(Magazzino_t * mag){

    enter_monitor(&(mag->m));

    while(mag->numero_liberi == 0){
        wait_condition(&(mag->m),CV_FORNITORE);
    }

    int i = 0;

    while(i < DIM && mag->scaff[i].stato != LIBERO ){
            i++;
    }

    mag->scaff[i].stato = IN_USO;

    mag->livello_scorte++;

    leave_monitor(&(mag->m));


    sleep(2);
    printf("fornisco   \n");

    mag->scaff[i].id_fornitore = getpid();




    enter_monitor(&(mag->m));

    mag->scaff[i].stato = OCCUPATO;

    mag->numero_liberi--;


    signal_condition(&(mag->m),CV_CLIENTE);

    leave_monitor(&(mag->m));


}


void Cliente(Magazzino_t * mag){

    enter_monitor(&(mag->m));

    while(mag->livello_scorte == 0){
        wait_condition(&(mag->m),CV_CLIENTE);
    }

    int i = 0;

    while(i < DIM && mag->scaff[i].stato != OCCUPATO ){
            i++;
    }

    mag->scaff[i].stato = IN_USO;

    mag->livello_scorte--;

    leave_monitor(&(mag->m));


    sleep(2);

    printf("acquisto %d\n",mag->scaff[i].id_fornitore);



    enter_monitor(&(mag->m));


    mag->scaff[i].stato = LIBERO;

    mag->numero_liberi++;

    signal_condition(&(mag->m),CV_FORNITORE);


    leave_monitor(&(mag->m));

}
