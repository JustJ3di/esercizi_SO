#ifndef MONITOR_H
#define MONITOR_H



typedef struct monitor{

    int mutex;

    int urgent_sem;

    int num_var_cond;

    int id_cond;

    int id_shared;

    int *cond_count;

    int *urgent_count;

}Monitor;

void init_monitor(Monitor *,int);

void enter_monitor(Monitor *);  

void signal_cond(Monitor *,int);

void wait_cond(Monitor *,int);

int queue_condition(Monitor*,int);

void leave_monitor(Monitor *);

void destroy_monitor(Monitor *);







#endif
