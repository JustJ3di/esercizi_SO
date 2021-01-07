#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "header.h"

#define NUM_REQ 5


int main(){
        int id_send,id_res;
        pid_t pid;

        key_t key_send,key_res;
        key_send =ftok(PATH_KEY_REQUEST,ALFA_KEY); //Aggiungere il codice per generare la chiave
        key_res = ftok(PATH_KEY_REQUEST,BETA_KEY); //Aggiungere il codice per generare la chiave

        id_send = msgget(key_send,IPC_CREAT|0664);//Aggiungere il codice per ottenere il descrittore della coda
        id_res = msgget(key_res,IPC_CREAT|0664);//Aggiungere il codice per ottenere il descrittore della coda

	printf("[DEBUG] - client id1 %d, id2 %d\n",id_send,id_res);	
	printf("[Client %d] - invio richieste...\n",getpid());


	int i = 0;
	Messaggio mes;	
	Risposta res;

	srand(time(NULL));

	while(i < NUM_REQ){

		mes.type = TYPE_REQ;
		mes.pid = getpid();
		mes.op1 = rand()%10;
		mes.op2 = rand()%10;

		// Invio di una richiesta
		printf("[Client %d] - Invio richiesta {%d,%d} al server...\n",getpid(),mes.op1,mes.op2);
		msgsnd(id_send,&mes,sizeof(Messaggio)-sizeof(long),0);

		// In attesa della risposta
		msgrcv(id_res,&res,sizeof(Risposta)-sizeof(long),getpid(),0);
		printf("[Client %d] - Ho ricevuto il risultato %d\n",getpid(),res.risultato);

		i++;
	}


	printf("[Client %d] - Fine processo\n",getpid());

	return 0;
}
