#include "sensore.h"
#include "aggregatore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

void aggregatore(int id_coda_sensore, int id_code_collettori[3]) {

    printf("Avvio processo aggregatore...\n");

    pthread_t scrittore;
    pthread_t lettore[3];

    MonitorLS *l = (MonitorLS *)malloc(sizeof(MonitorLS));

    pthread_mutex_init(&(l->mutex),NULL);
    pthread_cond_init(&(l->cv_lett),NULL);
    pthread_cond_init(&(l->cv_scritt),NULL);

    l->coda_sensore = id_coda_sensore;
    l->code_collettori[0] = id_code_collettori[0];
    l->code_collettori[1] = id_code_collettori[1];
    l->code_collettori[2] = id_code_collettori[2];


    

    l->num_lett = l->num_scritt = 0;
    l->wait_lett = l->wait_scritt = 0;

    pthread_create(&scrittore,NULL,thread_scrittore,(void *)l);

        

        pthread_create(&lettore[0],NULL,thread_lettore_1,(void *)l);

  

        pthread_create(&lettore[1],NULL,thread_lettore_2,(void *)l);
    

        pthread_create(&lettore[2],NULL,thread_lettore_3,(void *)l);

    for (size_t i = 0; i < 3; i++)
    {
    pthread_join(lettore[i],NULL);
    }
    pthread_join(scrittore,NULL);
    
   // pthread_mutex_destroy((l))

    /* TBD: Completare questa funzione, avviando un thread scrittore e 3 thread lettori *
     *
     *      Nota: occorre passare ai thread sia il puntatore ad un oggetto-monitor,
     *      sia l'identificativo della coda di messaggi su cui ricevere/inviare.
     */

    pthread_mutex_destroy(&(l->mutex));
    pthread_cond_destroy(&(l->cv_lett));
    pthread_cond_destroy(&(l->cv_scritt));


}
void * thread_lettore_2(void * x) {

    MonitorLS *ls = (MonitorLS *)x;



    for(int i=0; i<10; i++) {

        int valore;

        sleep(1);

        /* TBD: Chiamare il metodo "lettura()" del monitor */
        
        lettura(ls,&valore);

        printf("Aggregatore: Invio valore=%d\n", valore);

        messaggio msg={TIPO,valore};

        /* TBD: Inviare il messaggio */
        msgsnd(ls->code_collettori[1],(void *)&msg,SIZEOF(msg),0);
        

    }


    pthread_exit(NULL);
}
void * thread_lettore_1(void * x) {

    MonitorLS *ls = (MonitorLS *)x;




    for(int i=0; i<10; i++) {

        int valore;

        sleep(1);

        /* TBD: Chiamare il metodo "lettura()" del monitor */
        
        lettura(ls,&valore);

        printf("Aggregatore: Invio valore=%d\n", valore);

        messaggio msg={TIPO,valore};

        /* TBD: Inviare il messaggio */
        msgsnd(ls->code_collettori[0],(void *)&msg,SIZEOF(msg),0);
        

    }


    pthread_exit(NULL);
}


void * thread_lettore_3(void * x) {

    MonitorLS *ls = (MonitorLS *)x;




    for(int i=0; i<10; i++) {

        int valore;

        sleep(1);

        /* TBD: Chiamare il metodo "lettura()" del monitor */
        
        lettura(ls,&valore);

        printf("Aggregatore: Invio valore=%d\n", valore);

        messaggio msg={TIPO,valore};

        /* TBD: Inviare il messaggio */
        msgsnd(ls->code_collettori[2],(void *)&msg,SIZEOF(msg),0);
        

    }


    pthread_exit(NULL);
}

void * thread_scrittore(void * x) {

    MonitorLS *ls = (MonitorLS *)x;

    for(int i=0; i<10; i++) {

        printf("Aggregatore: In attesa di messaggi...\n");

        /* TBD: Ricevere il messaggio */
        messaggio msg;

        msgrcv(ls->coda_sensore,(void *)&msg,SIZEOF(msg),TIPO,0);

        int valore =  msg.valore;/* TBD */

        printf("Aggregatore: Ricevuto valore=%d\n", valore);

        /* TBD: Chiamare il metodo "scrittura()" del monitor */

        scrittura(ls,valore);

    }

    pthread_exit(NULL);
}

void lettura(MonitorLS * m, int * valore) {

    /* TBD: Completare il metodo, con la sincronizzazione */

    pthread_mutex_lock(&(m->mutex));

    while (m->num_scritt > 0)
    {
        m->wait_lett++;
        pthread_cond_wait(&(m->cv_lett),&(m->mutex));
        m->wait_lett--;
    }
    
    m->num_lett++;
    

    pthread_mutex_unlock(&(m->mutex));


    *valore = m->variabile;

    printf("Aggregatore: Lettura valore=%d\n", *valore);


    pthread_mutex_lock(&(m->mutex));

    m->num_lett--;

    if (m->num_lett == 0)
    {
        pthread_cond_signal(&(m->cv_scritt));
    }
    
    pthread_mutex_unlock(&(m->mutex));


}

void scrittura(MonitorLS * m, int valore) {
    
    /* TBD: Completare il metodo, con la sincronizzazione */

    pthread_mutex_lock(&(m->mutex));

    while (m->num_lett > 0 || m->num_scritt>0)
    {
        m->wait_scritt++;
        pthread_cond_wait(&(m->cv_scritt),&(m->mutex));
        m->wait_scritt--;
    }
    
    m->num_scritt++;

    pthread_mutex_unlock(&(m->mutex));

    printf("Aggregatore: Scrittura valore=%d\n", valore);



    m->variabile = valore;


    pthread_mutex_lock(&(m->mutex));

    m->num_scritt--;

    if (m->wait_scritt > 0)
    {
        pthread_cond_signal(&(m->cv_scritt));
    }else
    {
        pthread_cond_broadcast(&(m->cv_lett));
    }
    
    

    pthread_mutex_unlock(&(m->mutex));

}