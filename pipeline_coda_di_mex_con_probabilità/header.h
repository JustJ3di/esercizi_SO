#ifndef HEADER_H
#define HEADER_H


typedef struct header
{
    
    long type_mex;

    char string[64];


}Messaggio;



void initettore(int,int);

void server(int);

#endif
