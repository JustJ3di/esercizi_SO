#ifndef PROD_CONS
#define PROD_CONS

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void produttore(int *msg,int id_sem);


void consumatore(int *msg,int id_sem);


#endif