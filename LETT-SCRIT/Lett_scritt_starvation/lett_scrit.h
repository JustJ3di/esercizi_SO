#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>


#define MAX_LETTORI 5
#define MAX_SCRITTORI 5
#define MAX_PROCESSI 10

typedef struct lett_scrit {

    int index_lett;
    int msg;

}lett_scrit_t;


void lettori(lett_scrit_t *ps,int sem_id);

void scrittori(lett_scrit_t *ps,int sem_id);
