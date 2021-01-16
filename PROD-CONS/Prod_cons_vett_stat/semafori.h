#ifndef SEMAFORI
#define SEMAFORI

#define MSG_DISP 1
#define SPA_DISP 0

#define MUTEX_P 2
#define MUTEX_C 3


#include<errno.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdlib.h>

int init_sem(key_t key,int num_sem);

int sem_wait(int sem_id,int num_sem);
int sem_signal(int sem_id,int num_sem);


#endif