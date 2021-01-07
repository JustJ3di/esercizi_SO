/*TBD: Definire le macro necessarie */
#ifndef HEADER_H
#define HEADER_H

#define PATH_KEY "."
#define KEY_CONTOLL 'a'
#define KEY_PROXY  'b'


#define OKS_SEND 10
#define RTS_SEND 11

#define PARTENZE 1
#define ARRIVI 2

// Struttura che definisce un Volo
typedef struct {
    
    /* To be completed */

    long tipo;
    
    int ID;
    char direzione [10];
    char citta_partenza [20];
    char citta_arrivo [20];

}Volo;

/* Struttura che definisce un messaggio di controllo per implementare
 * la send sincrona
 */
typedef struct {
    
    /* To be completed */
    long tipo;

    int value;
    
}Control;

void controllore(int ds_queue_control_proxy);
void proxy(int ds_queue_control_proxy, int ds_queue_proxy_gestori);
void gestore_arrivi(int ds_queue_proxy_gestori);
void gestore_partenze(int ds_queue_proxy_gestori);

void initServiceQueues();
void removeServiceQueues();


#endif