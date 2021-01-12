#ifndef HEADER_H
#define HEADER_H

#define N_CLIENT 5
#define MEX_CLIENT 15

typedef struct 
{
    
    long type;

    int pid_client;

}Messaggio;


void client(int,int);

void server(int,int);

void printer(int);



#endif
