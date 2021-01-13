#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>

#include"header.h"

int main(){

    int shm_o = shmget(IPC_PRIVATE,sizeof(MonitorOperandi),IPC_CREAT|0664);
    int shm_r = shmget(IPC_PRIVATE,sizeof(MonitorRisultati),IPC_CREAT|0664);

    MonitorOperandi *mo = (MonitorOperandi *)shmat(shm_o,NULL,0);
    MonitorRisultati *mr =(MonitorRisultati *)shmat(shm_r,NULL,0);

    init_monitor(&(mo->M),2);
    init_monitor(&(mr->M),2);

    mo->coda = mo->testa = 0;
    mo->count = 0;

    for (size_t i = 0; i < 5; i++)
    {
        mr->stato[i] = LIBERO;
    }
    mr->liberi = 5;
    mr->occupati = 0;
    


    pid_t gen_op,prel_ris,calcolo;

    for (size_t i = 0; i < 2; i++)
    {
        gen_op = fork();

        if (gen_op == 0)
        {
                srand(getpid());
                for(int i = 0;i<6;i++){
                    inserisci_operando(mo,rand()%10+1);
                }
                exit(1);
        }
        
        
    }
    

    for (size_t i = 0; i < 3; i++)
    {
        calcolo = fork();


        if (calcolo == 0)
        {

            int calc;
            for (size_t i = 0; i < 2; i++)
            {
                int *op;
                op = preleva_operando(mo);

                int x = *(op);
                int y = *(op+1);

                printf("operandi   %d   %d\n",x,y);

                calc = (x*x) + (y*y);
                inserisci_risultato(mr,calc);
            }
            exit(1);
        }
        

    }
    
    prel_ris = fork();

    if (prel_ris == 0)
    {
        int high = 0;
        int low = 0;
        for (size_t i = 0; i < 6; i++)
        {
            int ris = preleva_risultato(mr);

            if (ris > 50)
            {
                high++;
            }else
            {
                low++;
            }
            
            printf("risultato %d\n",ris);

        }

        printf(">50 %d, <50 %d  \n",high,low);

        exit(1);
    }
    
    

    for (size_t i = 0; i < 6; i++)
    {
        wait((void *)0);
    }

    remove_monitor(&(mo->M));
    remove_monitor(&(mr->M));

    shmctl(shm_o,IPC_RMID,0);
    shmctl(shm_r,IPC_RMID,0);

    




    return 0;


}
