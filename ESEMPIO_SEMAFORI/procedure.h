#ifndef SEMAPHORE_H
#define PROCEDURE_H


#include<stdio.h>
#include<errno.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

int wait_sem(int id_sem,int numsem);

int signal_sem(int id_sem,int numsem);

#endif
