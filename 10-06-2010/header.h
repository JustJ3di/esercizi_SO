#ifndef HEADER_H
#define HEADER_H

#define NUM_LETTORI 10


#define CV_SCRITTORI 0
#define CV_LETTORI 1

#include"monitor.h"



typedef struct header
{

    int temperatura;
    unsigned int umidita;
    unsigned short pioggia;

//monitor


    int num_lettori;
    int num_scrittori;

    Monitor M;

}Meteo;


void Scrittura(Meteo *);
void Lettura(Meteo *);

#endif