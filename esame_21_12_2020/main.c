#include "prodcons.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void * Produttore(void *);
void * Consumatore(void *);

int main() {

    /* TBD: Avviare i thread produttore e consumatore */
    pthread_t prod;
    pthread_t cons;

    MonitorStreaming *p = (MonitorStreaming *)malloc(sizeof(MonitorStreaming));

    inizializza(p);

    pthread_create(&prod,NULL,Produttore,(void *)p);
    pthread_create(&cons,NULL,Consumatore,(void *)p);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    
    distruggi(p);    

    free(p);

    return 0;
    

}

void * Produttore(void * p) {

    MonitorStreaming *m = (MonitorStreaming *)p;

    for(int i=0; i<10; i++) {

        Frame f;
        f[0][0] = rand() % 11;
        f[0][1] = rand() % 11;
        f[1][0] = rand() % 11;
        f[1][1] = rand() % 11;

        /* TBD: Chiamare il metodo "produci()" del monitor */
        produci(m,f);

        sleep(1);
    }

    pthread_exit(NULL);
}

void * Consumatore(void * p) {

    MonitorStreaming *m = (MonitorStreaming *)p; 

    /* TBD: Chiamare il metodo "bufferizza()" del monitor */
    //bufferizza(m,4);

    for(int i=0; i<10; i++) {

        Frame f;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
        consuma(m,f);

        sleep(1);
    }

    pthread_exit(NULL);
}
