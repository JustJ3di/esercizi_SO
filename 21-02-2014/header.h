#ifndef HEADER_H
#define HEADER_H

#include<pthread.h>

#define STAZIONE 4

typedef struct treno{

    int stazione;

    int num_lettori;
    int num_scrittori;
    int wait_scrittori;
    int wait_lettori;

    pthread_mutex_t mutex;
    pthread_cond_t cv_lettore;
    pthread_cond_t cv_scittore; 


}MonitorTreno;

void inizializza(MonitorTreno *m);
void rimuovi(MonitorTreno *m);
int leggi_stazione(MonitorTreno *m);
void scrivi_stazione(MonitorTreno *m);



#endif
