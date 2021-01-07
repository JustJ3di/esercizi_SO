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

    MonitorStreaming *m = (MonitorStreaming *)malloc(sizeof(MonitorStreaming));

    inizializza(m);

    pthread_create(&prod,NULL,Produttore,(void *)m);

    pthread_create(&cons,NULL,Consumatore,(void *)m);

    pthread_join(cons,NULL);
    pthread_join(prod,NULL);

    distruggi(m);
    free(m);

    return 0;
    


}

void * Produttore(void * p) {

    MonitorStreaming *m = (MonitorStreaming *)p;

    int tempo_attesa = 1000000;

    for(int i=0; i<12; i++) {

        Frame f;
        f[0][0] = rand() % 11;
        f[0][1] = rand() % 11;
        f[1][0] = rand() % 11;
        f[1][1] = rand() % 11;

        /* TBD: Chiamare il metodo "produci()" del monitor,
         *      incrementare "tempo_attesa" se il valore di ritorno è "1"
         */
        int x = produci(m,f);

        if (x == 1)
        {
            tempo_attesa = tempo_attesa +500000;
        }
        

        usleep(tempo_attesa);
    }

    pthread_exit(NULL);
}

void * Consumatore(void * p) {

    MonitorStreaming *m = (MonitorStreaming *)p;

    for(int i=0; i<12; i++) {

        Frame f;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
        consuma(m,f);

        sleep(3);
    }

    pthread_exit(NULL);
}
