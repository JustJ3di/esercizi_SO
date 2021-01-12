#ifndef HEADER_H
#define HEADER_H

#define CV_SCRITTORI_HIGH_PRIORITY 0
#define CV_SCRITTORI_LOW_PRIORITY  1
#define CV_LETTORI 2

#define N_LETTORI 3
#define N_SCRITTORI_H 2
#define N_SCRITTORI_L 2

#include"monitor_signal_continue.h"

typedef struct header
{

    int buffer;

    int num_lett;
    
    int num_scritt;

    int num_scrittore_high_prority;

    int num_lettori_attesa;

    Monitor M;
    
}Monitor_ls;

void Lettori(Monitor_ls *);

void Scrittori_high(Monitor_ls *);

void Scrittori_low(Monitor_ls *);


#endif
