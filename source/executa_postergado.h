//executa_postergado.h
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define true 1
#define false 0

typedef struct message message_t;


/*
Auxiliary methods. Should these be protected/private?
*/
int retrieve_queue_id();
char* parse_clarg_filename(char *argv[]);
int* parse_clarg_delay(char *argv[]);