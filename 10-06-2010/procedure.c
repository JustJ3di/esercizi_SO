#include"header.h"
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>

void Lettura(Meteo * meteo){

    enter_monitor(&(meteo->M));

    while (meteo->num_scrittori > 0)
    {
        wait_condition(&(meteo->M),CV_LETTORI);
    }

    meteo->num_lettori++;

    leave_monitor(&(meteo->M));
    

    printf("temperatura <%d> umidità <%d> pioggia <%d>\n",meteo->temperatura,meteo->umidita,meteo->pioggia);


    enter_monitor(&(meteo->M));

    meteo->num_lettori--;

    if (meteo->num_lettori == 0)
    {
        signal_condition(&(meteo->M),CV_SCRITTORI);
    }
    
    leave_monitor(&(meteo->M));

}


void Scrittura(Meteo *meteo){


    enter_monitor(&(meteo->M));

    while (meteo->num_lettori > 0 || meteo->num_scrittori > 0)
    {
        wait_condition(&(meteo->M),CV_SCRITTORI);
    }
    
    meteo->num_scrittori++;

    leave_monitor(&(meteo->M));

    srand(time(NULL));

    meteo->pioggia = rand()%2;

    meteo->umidita = rand()%101 - 50;

    meteo->temperatura = rand()%101;

    

    enter_monitor(&(meteo->M));

    meteo->num_scrittori--;

    if (queue_condition(&(meteo->M),CV_SCRITTORI) > 0)
    {
        signal_condition(&(meteo->M),CV_SCRITTORI);

    }else if (queue_condition(&(meteo->M),CV_LETTORI) > 0  )
    {
        signal_condition(&(meteo->M),CV_LETTORI);
    }
    
    
    leave_monitor(&(meteo->M));


}