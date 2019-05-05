//executa_postergado.h
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <stdbool.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

typedef struct message message_t;


/*
Auxiliary methods. Should these be protected/private?
*/
int retrieve_queue_id();
const char * parse_clarg_filename(int argc, char *argv[]);
unsigned int parse_clarg_delay(int argc, char *argv[]);