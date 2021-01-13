#ifndef HEADER_H
#define HEADER_H

#define NUM_CLIENT 8
#define NUM_SERVER 3

#define  SIZEOF(msg) sizeof(msg)-sizeof(long)

typedef struct header
{
    
    long tipo;

    int contenuto;

}Messaggio;




#endif
