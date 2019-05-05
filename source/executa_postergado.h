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
Main methods
*/
int retrieve_queue_id();
bool send_message( message_t message_to_send, int queue_id );

/*
Auxiliary methods. Should these be protected/private?
*/
const char * parse_clarg_filename(int argc, char *argv[]);
unsigned int parse_clarg_delay(int argc, char *argv[]);