#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include"header.h"

void *Consumatore(void *gio){

    GestioneIO *g = (GestioneIO *)gio;

    Buffer b;

    for(int i = 0;i<4;i++)
    {

        while (!Consuma(g,&b))
        {
            printf("dato<%d> e indirizzo<%d>\n",b.dato,b.indirizzo);
        }
        
            printf("Buffer vuoto\n");
            sleep(3);
        
        
        

    }
    
    pthread_exit(NULL);

}


void *Produttore(void *gio){

    GestioneIO *g =(GestioneIO *)gio;

    Buffer b;
    b.dato= rand()%11;
    b.indirizzo = rand()%11;

    for (size_t i = 0; i < 3; i++)
    {
        
        Produci(g,&b);

        b.dato = b.dato +1;
        b.indirizzo = b.indirizzo + 1;

        sleep(1);
    
    }
    
    pthread_exit(NULL);

}


int main(){

    pthread_t thread_produttori[4];
    pthread_t thread_consumatori[2];

    GestioneIO *gio = (GestioneIO *)malloc(sizeof(GestioneIO));

    Inizializza(gio);

    srand(time(NULL));
    for (size_t i = 0; i < 4; i++)
    {
        printf("produzione  \n");
        pthread_create(&thread_produttori[i],NULL,Produttore,(void *)gio);
    }

    for (size_t i = 0; i < 2; i++)
    {
        printf("consumatore\n");
        pthread_create(&thread_consumatori[i],NULL,Consumatore,(void *)gio);
    }
    

    for (size_t i = 0; i < 4; i++)
    {
        pthread_join(thread_produttori[i],NULL);
    }
    
    for (size_t i = 0; i < 2; i++)
    {
        pthread_join(thread_consumatori[i],NULL);
    }
    

    Rimuovi(gio);

    free(gio);


    return 0;

}