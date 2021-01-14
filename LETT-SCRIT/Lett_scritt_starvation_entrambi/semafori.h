#include<sys/sem.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>

#define MUTEXL 0
#define SYNC 1

#define MUTEXS 2

#define MUTEX 3

int init_sem(key_t key,int num_sem);

int Signal_sem(int sem_id,int sem_index);

int Wait_sem(int sem_id,int sem_index);