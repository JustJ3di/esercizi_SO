#include "sensore.h"
#include "aggregatore.h"
#include "collettore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {


    /* TBD: Creare le code di messaggi, 
     * e avviare i processi sensore, aggregatore, e collettore 
     * 
     * 
     */

    int  coda_sens = msgget(IPC_PRIVATE,IPC_CREAT|0664);

    int coda_coll[3];

    for (size_t i = 0; i <3; i++)
    {
        coda_coll[i] = msgget(IPC_PRIVATE,IPC_CREAT|0664);
        printf("%d\n",coda_coll[i]);
    }


    pid_t pdi = fork();

    if (pdi == 0)
    {
        sensore(coda_sens);
        exit(1);
    }



    pid_t pid ;

    pid = fork();

    if (pid == 0)
    {
        collettore(coda_coll[0]);
        exit(1);
    }


    pid = fork();

    if (pid == 0)
    {
        collettore(coda_coll[1]);
        exit(1);
    }


    pid = fork();

    if (pid == 0)
    {
        collettore(coda_coll[2]);
        exit(1);
    }


    

    pdi = fork();
    if(pdi == 0){
        aggregatore(coda_sens,coda_coll);
        exit(1);
    }


    for (size_t i = 0; i < 5; i++)
    {
        wait(NULL);
    }
    
    
    return 0;    
    
    
}
