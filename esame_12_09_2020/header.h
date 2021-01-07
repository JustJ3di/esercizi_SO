#ifndef __HEADER
#define __HEADER

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

// Aggiungere macro utilizzate per la generazione delle chiavi

#define PATH_KEY_REQUEST "."
#define ALFA_KEY 'a'

#define PATH_KEY_RISPOSTA "."
#define BETA_KEY 'b'
// Aggiungere macro che identifica il tipo di messaggio da utilizzare

#define TYPE_REQ 1
#define RISPOATA 2

#define MAX 2


typedef struct{
	long type;
	pid_t pid;
	int op1;
	int op2;
}Messaggio;

typedef struct{
	long type;
	int risultato;
}Risposta;

typedef struct{ 
    
    // Aggiungere le variabili per la sincronizzazione
	Messaggio msg[3];
	int count;
	int testa;
	int coda;

	pthread_mutex_t mutex;

	pthread_cond_t cv_prod;

	pthread_cond_t cv_cons;

    
}Buffer;

#endif
