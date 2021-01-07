#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

#define PATH_KEY "."

#define PATH_ORO 'a'
#define PATH_ARGENTO 'b'

#define TYPE_MEX 1

#define SIZEOF(msg) sizeof(msg)-sizeof(long)


/* TBD: Definire le macro necessarie per le code di messaggio */
 
typedef struct {
    
    /* TBD: Definire le variabili necessarie per la sincronizzazione */
    int num_lett;
    int num_scritt;
    int wait_scritt;
    
    pthread_mutex_t mutex;
    pthread_cond_t cv_lettori;
    pthread_cond_t cv_scrittori;
    //Var condivise
    int quotazione_oro;
    int quotazione_argento;
    
}LettScritt;

typedef struct {
    
    /* TBD: Definire i campi necessari per lo scambio di messaggi inerenti alla quotazione */

    long tipo; 

    int value;

    
} Msg_Quotazione;

void * seller(void *);
void * buyer(void *);

void scrivi_quotazione_oro(LettScritt *ls, int quotazione_oro);
void scrivi_quotazione_argento(LettScritt *ls, int quotazione_argento);
void leggi_quotazione_oro(LettScritt *ls, int);
void leggi_quotazione_argento(LettScritt *ls, int);

void InizioLetturaQuotazione(LettScritt * ls);
void FineLetturaQuotazione(LettScritt * ls);
void FineScritturaQuotazione(LettScritt * ls);
void InizioScritturaQuotazione(LettScritt * ls);


#endif
