#ifndef SEMAFORI_H
#define SEMAFORI_H

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>

#define SIZE_SEM 2

#define MUTEXL 0
#define SYNC 1



int init_sem(key_t,int);


int Wait_sem(int,int);

int Signal_sem(int,int);

#endif