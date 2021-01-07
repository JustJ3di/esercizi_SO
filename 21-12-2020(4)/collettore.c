#include "sensore.h"
#include "collettore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void collettore(int id_coda_collettore) {

    printf("Avvio processo collettore (id coda = %d)...\n", id_coda_collettore);


    for(int i=0; i<10; i++) {

        printf("Collettore: In attesa di messaggi...\n");

        /* TBD: Ricezione messaggio */

        messaggio msg;

        msgrcv(id_coda_collettore,(void *)&msg,SIZEOF(msg),0,0);

        int valore = msg.valore;/* TBD */

        printf("Collettore: Ricevuto valore=%d\n", valore);

    }
}