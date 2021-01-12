#ifndef HEADER_H
#define HEADER_H


#define REQUEST_TO_SENT 9
#define OK_TO_SEND      10



typedef struct header
{

    long tipo_mex;
    int val;

}Messaggio_t;


void init_service_queue();
void destroy_service_queue();

void client(int,Messaggio_t);

void interfaccia(int,int,int,int);

void server_1(int);

void server_2(int);

void server_3(int);


#endif
