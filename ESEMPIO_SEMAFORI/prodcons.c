#include "procedure.h"

int wait_sem(int id_sem,int numsem){

    struct sembuf sem_buf;

    sem_buf.sem_num = numsem;
    sem_buf.sem_flg = 0;
    sem_buf.sem_op = -1;

    int err = semop(id_sem,&sem_buf,1);

    if(err < 0){
        perror("errore nella wait");
    }

    return err;
}

int signal_sem(int id_sem,int numsem){

    struct sembuf sem_buf;

    sem_buf.sem_num = numsem;
    sem_buf.sem_flg = 0;
    sem_buf.sem_op = 1;

    int err = semop(id_sem,&sem_buf,1);

    if(err < 0){
        perror("errpre nella wait");
    }

    return err;
}
