#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<signal.h>
#include<wait.h>
#include<string.h>

typedef struct message message_t;
typedef struct execution_entry execution_entry_t;
typedef struct execution_queue execution_queue_t;

/*
 * Global variables so signal handler can access them
 */ 
execution_queue_t * exec_queue;
int flag = 0;
int busy = 0;
