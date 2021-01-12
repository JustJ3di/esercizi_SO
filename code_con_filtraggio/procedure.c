#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<string.h>

#include"header.h"

int crea_code(key_t key){

    int queue = msgget(key,IPC_CREAT|0664);

    if (queue < 0)
    {
        perror("errore queue");
        exit(1);
    }
    
    return queue;

}






void generatore(int queue){


    for(int i = 0;i<2;i++){

        Messaggio msg;

        srand(getpid());

       //carattere fine stringa
        int len_string = rand()%10 +1;  //random tra 0 e 9 con off_set di 1 quindi 1<len_string<11

        for (size_t i = 0; i <len_string ; i++)  //qui creo la stringa
        {
            msg.string[i] = rand()%26 + 'a';
        }
        msg.string[len_string++] = '\0';  //setto il carattere terminatore  ,che può essere massimo l' 11-esimo carattere 


        for (size_t i = 0; i < 2; i++)
        {
            msg.array[i] = rand()&10;
        }

        msg.TIPO = 1;

        msg.sum = 0;

        

        int err = msgsnd(queue,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);
    
        if (err < 0)
        {
            perror("error send\n");
            exit(1);
        }
        
    
    }
}

//............filtro..........

void filtro(int queue_gen,int queue_fil){

    int count = 0;
    int err;

    for(int i = 0;i<2*3;i++){

        Messaggio msg;


        err = msgrcv(queue_gen,(void*)&msg,sizeof(Messaggio)-sizeof(long),0,0);  //ricevo dai generatori

        if (err < 0)
        {
            perror("send error\n");
            exit(1);
        }
        


        if (strchr(msg.string,'x') == 0)   
        {
            err = msgsnd(queue_fil,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);
            if(err < 0){
                perror("send error\n");
                exit(1);
            }
            
            count++;

        }

        
    }

//condizione da mandare al checksum per terminare
    Messaggio msg_cond;

    if (count != 6  )
    {
        msg_cond.TIPO = TYPE_EXIT;

        err = msgsnd(queue_fil,(void*)&msg_cond,sizeof(Messaggio)-sizeof(long),0);

        if (err < 0)
        {
            perror("send error \n");
        }
        

    }
    
}

//....................checksum..........

void checksum(int queue_fil,int queue_vis){

    int err;
    

    for (size_t i = 0; i < 6; i++)
    {
        Messaggio msg;
  
        err = msgrcv(queue_fil,(void *)&msg,sizeof(Messaggio)-sizeof(long),0,0);

        if (err < 0)
        {
            perror("send error\n");
            exit(1);
        }
        

    //controllo se mi arriva un tipo exit

        if(msg.TIPO == TYPE_EXIT){
            strcpy(msg.string,"termina");
            
            
            err = msgsnd(queue_vis,(void*)&msg,sizeof(Messaggio)-sizeof(long),0);  // dico al visualizzatore che deve terminare
            
            if (err < 0)
            {
                perror("send error\n");
                exit(1);                
            }
            
            
            exit(1);
        }    

//faccio le somme

        for (size_t i = 0; i < 2; i++)
        {
            msg.sum = msg.array[i] +msg.sum;
        }
        
        err = msgsnd(queue_vis,(void *)&msg,sizeof(Messaggio)-sizeof(long),0);
        
        if (err < 0)
        {
            perror("send error\n");
            exit(1);
        }
        

    }
    
}

/**VISUALIZZATORE............*/

void visualizzatore(int queue_vis){

    int err;

    for (size_t i = 0; i < 6; i++)
    {

        Messaggio msg;

        err = msgrcv(queue_vis,(void *)&msg,sizeof(Messaggio)-sizeof(long),0,0);

        if (err < 0)
        {
            perror("send error\n");
            exit(1);           
        }
        


//controllo se devo terminare

        if(strcmp("termina",msg.string ) == 0 && msg.TIPO == TYPE_EXIT){

            printf("Termino\n");
            exit(1);

        }

        printf("MESSAGGIO....STRINGA %s    \t",msg.string);

        for (size_t i = 0; i < 2; i++)
        {
            printf("   valori array  %d  \t ",msg.array[i]);
        }
        
        printf("SOMMA %d\n",msg.sum);

        
        
    }
    

}


