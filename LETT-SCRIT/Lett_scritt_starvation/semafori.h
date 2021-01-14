#include<sys/sem.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>

#define MUTEX 0
#define SYNC 1

int init_sem(key_t key,int num_sem);

int Signal_sem(int sem_id,int sem_index);

int Wait_sem(int sem_id,int sem_index);