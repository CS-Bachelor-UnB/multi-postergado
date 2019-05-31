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


/* Including topologies */
#include "fattree.h"
#include "torus.h"

typedef struct message message_t;
typedef struct execution_entry execution_entry_t;
typedef struct execution_queue execution_queue_t;


/*
 * Global variables so signal handler can access them
 */
execution_queue_t * exec_queue;
execution_queue_t * exec_queue_done;
int busy = 0;
long process_pid[15]; 
