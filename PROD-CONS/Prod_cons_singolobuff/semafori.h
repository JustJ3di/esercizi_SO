#ifndef SEMAFORI
#define SEMAFORI

#define MSG_DISP 1
#define SPA_DISP 0


#include<errno.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdlib.h>

int init_sem(key_t key,int num_sem);

int sem_wait(int sem_id,int num_sem);
int sem_signal(int sem_id,int num_sem);


#endif