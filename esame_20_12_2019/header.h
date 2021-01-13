#ifndef HEADER_H
#define HEADER_H

#include"monitor.h"

#define CV_PROD 0
#define CV_CONS 1

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2    

typedef struct
{
    
    int operandi[5];

    int count;
    int testa;
    int coda;
    Monitor M;

}MonitorOperandi;


typedef struct
{


    int risultati[5];
    int stato[5];

    int liberi;
    int occupati;

    Monitor M;


}MonitorRisultati;

void inserisci_operando(MonitorOperandi *mo,int operando);
int *preleva_operando(MonitorOperandi *mo);
void inserisci_risultato(MonitorRisultati * mr,int risultati);
int preleva_risultato( MonitorRisultati *mr);

#endif
