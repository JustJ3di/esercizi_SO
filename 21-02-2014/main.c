#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include"header.h"

void *scrivo(void *m){

    MonitorTreno *mt =(MonitorTreno *)m;

    for(int i = 0;i < 10;i++){    
    
        scrivi_stazione(mt);
        sleep(3);
        printf("[CAPITRENO]  scrivo....\n");
    
    }
    pthread_exit(NULL);

}

void *leggo(void *m){

    MonitorTreno *mt = (MonitorTreno *)m;

    for (size_t i = 0; i < 3; i++)
    {

        int x = leggi_stazione(mt);
        sleep(rand()%6+1);
        printf("[VIAGGIATORI]leggo la stazione  <%d>\n",x);

    }
    
    pthread_exit(NULL);
}

int main(){

    pthread_t  capitreno[4];
    pthread_t  viaggiatori[10];
    pthread_attr_t attr;

    srand(time(NULL));

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    MonitorTreno *m[STAZIONE];    

    for (size_t i = 0; i < STAZIONE; i++)
    {
        m[i] = (MonitorTreno *)malloc(sizeof(MonitorTreno));
        inizializza(m[i]);
    }
    
    printf("MONITOR STAZIONE INIZIALIZZATI\n");

    sleep(2);

    for (size_t i = 0; i < 4; i++)
    {
        pthread_create(&capitreno[i],&attr,scrivo,(void *)m[i]);
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_create(&viaggiatori[i],&attr,leggo,(void *)m[rand()%4]);
    }


    for (size_t i = 0; i < 4; i++)
    {
        pthread_join(capitreno[i],NULL);
    }
    
    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(viaggiatori[i],NULL);
    }
    
    printf("RIMUOVO MONITOR STAZIONI\n");
    sleep(1);

    for (size_t i = 0; i < STAZIONE; i++)
    {
        rimuovi(m[i]);
        free(m[i]);
    }
    

    pthread_attr_destroy(&attr);    


    return 0;


}
