#include"header.h"
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


void Inizializza(GestioneIO *p){

    pthread_cond_init(&(p->cv_produttore),NULL);
    
    pthread_mutex_init(&(p->mutex),NULL);

    p->count = 0;
    p->tail = p->head = 0;

}

void *Produttore(void * p){

    GestioneIO *pc = (GestioneIO *)p;
    srand(time(NULL));

    Buffer *b = (Buffer *)malloc(sizeof(Buffer));

    b->dato = rand()%10;
    b->indirizzo = rand()%10;


    for (size_t i = 0; i < 3; i++)
    {
    
        b->indirizzo++;
        b->dato++;

        Produci(pc,b);
        sleep(1);

    }

    free(b);

    pthread_exit(NULL);

}


void *Consumatore(void *p){

    GestioneIO *pc = (GestioneIO *)p;

    int result;
    
    Buffer *b = (Buffer *)malloc(sizeof(Buffer));

    b->dato = rand()%11;
    b->indirizzo = rand()%11;

    for(int i  = 0;i<4;i++)
    {

        result = Consuma(pc,b);

        sleep(3);

        if (result == 0)
        {
        
            printf("valore trovato\n");

        } 
        else
        {
    
            printf("valore non trovato \n");
        
        }
    
    }

    free(b);
    
    

    pthread_exit(NULL);

}


void Produci(GestioneIO *pc,Buffer *b){

    pthread_mutex_lock(&(pc->mutex));

    while(pc->count == SIZE){

        pthread_cond_wait(&(pc->cv_produttore),&(pc->mutex));

    }

    pc->vettore[pc->head].dato = b->dato ;
    pc->vettore[pc->head].indirizzo = b->indirizzo;

    printf("Produttore dato : <%d>   e indirizzo <%d>\n",pc->vettore[pc->head].dato,pc->vettore[pc->head].indirizzo);

    pc->head = (pc->head + 1)%SIZE;

    pc->count++;

    pthread_mutex_unlock(&(pc->mutex));

}

int Consuma(GestioneIO *pc,Buffer *b){

    pthread_mutex_lock(&(pc->mutex));

    if (pc->count == 0)
    {
        
        pthread_mutex_unlock(&(pc->mutex));

        return 1;

    }
    else
    {
        
        b->indirizzo = pc->vettore[pc->tail].dato;
        b->dato = pc->vettore[pc->tail].indirizzo; 

        printf("Consumatore dato : <%d>   e indirizzo <%d>\n",b->dato,b->indirizzo);   

        pc->count--;

        pc->tail = (pc->tail + 1)%SIZE;
        
        pthread_cond_signal(&(pc->cv_produttore));

        pthread_mutex_unlock(&(pc->mutex));

        return 0;

    }


}
