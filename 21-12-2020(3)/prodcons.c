#include "prodcons.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>


void inizializza(MonitorStreaming * p) {

    /* TBD: Inizializzare il monitor */
    init_monitor(&(p->M),2);

    p->coda = 0;
    p->testa = 0;
    p->count = 0;

}


void produci(MonitorStreaming * p, char * stringa, size_t lunghezza, key_t chiave) {

    /* TBD: Completare il metodo, con la sincronizzazione */

    enter_monitor(&(p->M));

    if (p->count ==  DIM)
    {
        wait_condition(&(p->M),CV_PROD);
    }
    

    printf("Avvio produzione...\n");
 

    sleep(1);

    int shm_id = shmget(chiave,(lunghezza),IPC_CREAT|0664);

    char * stringa_shm = (char *)shmat(shm_id,NULL,0); /* TBD: Creare una nuova shared memory, su cui copiare la stringa */

    /* TBD */p->vettore[p->testa].dimensione = lunghezza;
    /* TBD */p->vettore[p->testa].chiave = chiave;
    /* TBD */p->vettore[p->testa].produttore = getpid();
             p->vettore[p->testa].stato = OCCUPATO;
             p->count++;
             p->testa = (p->testa +1)%DIM;

    strcpy(stringa_shm, stringa);   // Copia della stringa


    printf("Produzione completata: %s (%zu char, key=%x)\n", stringa_shm, lunghezza, chiave);

    shmdt((void *)stringa_shm);


    signal_condition(&(p->M),CV_CONS);

    leave_monitor(&(p->M));    


}

void consuma(MonitorStreaming * p, char * stringa, size_t * lunghezza) {

    /* TBD: Completare il metodo, con la sincronizzazione */

    enter_monitor(&(p->M));



    if (p->count == 0)
    {
        wait_condition(&(p->M),CV_CONS);
    }
    


    

    printf("Avvio consumazione...\n");

    sleep(1);

    key_t chiave =p->vettore[p->coda].chiave;/* TBD */
    pid_t produttore = p->vettore[p->coda].produttore;/* TBD */
    *lunghezza = p->vettore[p->coda].dimensione;/* TBD */
    int shm_id = shmget(chiave,(*lunghezza),IPC_CREAT|0664);
    p->vettore[p->coda].stato = LIBERO;
    p->coda = (p->coda+1)%DIM;
    p->count--;

    char * stringa_shm =(char *)shmat(shm_id,NULL,0);/* TBD: Accedere alla stringa su shared memory */

    strcpy(stringa, stringa_shm);   // Copia della 



    printf("Consumazione completata: %s (%zu char, key=%x)\n", stringa, *lunghezza, chiave);

    shmdt((void *)stringa_shm);



    signal_condition(&(p->M),CV_PROD);
    leave_monitor(&(p->M));

}

void distruggi(MonitorStreaming * p) {

    /* TBD: Completare il metodo */

    remove_monitor(&(p->M));

}