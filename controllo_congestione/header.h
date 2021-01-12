#ifndef HEADER_H
#define HEADER_H

#define TOKEN 5

typedef struct header
{

    long tipo_mex;

    int val;

}Messaggio_t;


void produzione(int,Messaggio_t);
void consumazione(int);

#endif