#include "sensore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

void sensore(int id_coda_sensore) {

    printf("Avvio processo sensore...\n");


    srand(time(NULL));

    for(int i=0; i<10; i++) {

        int valore = rand() % 11;

        printf("Sensore: Invio valore=%d\n", valore);
        messaggio msg = {TIPO,valore};

        /* TBD: Invio messaggio */
        msgsnd(id_coda_sensore,(void *)&msg,SIZEOF(msg),0);
        
        sleep(1);
    }
}