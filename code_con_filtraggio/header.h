#ifndef HEADER_H
#define HEADE_H

#include<sys/types.h>


#define TYPE_EXIT 10


typedef struct header
{

    long TIPO;

    char string[11];
    int array[2];
    int sum;

}Messaggio;


int crea_code(key_t);

void generatore(int);  //coda generatore

void filtro(int,int); //coda generatore e coda cheksum

void checksum(int,int); //coda checksum e coda visual

void visualizzatore(int);  //coda visual


#endif