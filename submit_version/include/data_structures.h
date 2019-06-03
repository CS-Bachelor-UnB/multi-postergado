/*
 * Authors: 
 * André Luís Souto Ferreira 14/0016261
 * Otto Kristian von Sperling 12/0131510
 * Victor Fabre Figueiredo 15/0022948
 * 
 */

#include <time.h>
#include <wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <stdbool.h>
#include <sys/msg.h>
#include <sys/types.h>

typedef struct message message_t;
typedef struct cell cell_t;
typedef struct execution_entry execution_entry_t;
typedef struct execution_queue execution_queue_t;

/*
 * Global variables so signal handler can access them
 */
execution_queue_t * exec_queue;
execution_queue_t * exec_queue_done;
int busy = 0;
long process_pid[15];
