#include "fattree.h"

/*
Data Structure for the message to be exchanged between the nodes of the fat tree
*/ 
struct message
{
   long pid;
   char filename[500];
   unsigned int delta_delay;
};

int retrieve_queue_id(int type)
{
   /*
   Returns a standard queue_id shared with  the job_scheduler or zero in case it fails
   */
   int queue_id;
   extern int errno;

   if ( type == 0 && ( queue_id = msgget( 0x1200, (IPC_CREAT|0x1B6 ) ) ) < 0 )
   {
     perror( "\nRETRIEVE_QUEUE_ERROR: Error while retrieving the queue_id\n" );
     exit( errno );
   }

   else if ( type == 1 && ( queue_id = msgget( 0x6261, (IPC_CREAT|0x1B6 ) ) ) < 0 )
   {
     perror( "\nRETRIEVE_QUEUE_ERROR: Error while retrieving the queue_id\n" );
     exit( errno );
   }

   else
      return queue_id;
}

bool receive_message( message_t *message_received, int queue_id, long type )
{
   /**/
   extern int errno;

   if( msgrcv( queue_id, message_received, sizeof( *message_received ) - sizeof( long ), type, MSG_NOERROR ) < 0 )
   {
      // prints error message
      //perror("RECEIVE_MESSAGE_ERROR");
      
      return false;
   }

   else
      return true;
}

bool send_message( message_t message_to_send, int queue_id )
{
   /**/
   extern int errno;

   if( msgsnd( queue_id, &message_to_send, sizeof( message_to_send ) - sizeof( long ), 0 ) < 0 )
   {
      // prints error message
      //perror("SEND_MESSAGE_ERROR");
      exit( errno );
   }

   else
      return true;
}

void setup_fattree(char *arg, long * parent_type, long * child_type)
{
    /* 
       Obtaining types to be used when sending and receiving 
       messages with message queue. In other words, this function
       specifies the routes for each node of the tree.
    */
    if ( strcmp(arg,"a") == 0 )
    {
        *parent_type = 1;
        *child_type = 2;
    }
    else if ( strcmp(arg,"b") == 0 )
    {
        *parent_type = 2;
        *child_type = 3;
    }
    else if ( strcmp(arg,"c") == 0 )
    {
        *parent_type = 2;
        *child_type = 4;
    }
    else if ( strcmp(arg,"d") == 0 )
    {
        *parent_type = 3;
        *child_type = 5;
    }
    else if ( strcmp(arg,"e") == 0 )
    {
        *parent_type = 3;
        *child_type = 6;
    }
    else if ( strcmp(arg,"f") == 0 )
    {
        *parent_type = 4;
        *child_type = 7;
    }
    else if ( strcmp(arg,"g") == 0 )
    {
        *parent_type = 4;
        *child_type = 8;
    }
    else if ( strcmp(arg,"h") == 0 )
    {
        *parent_type = 5;
        *child_type = -1;
    }
    else if ( strcmp(arg,"i") == 0 )
    {
        *parent_type = 5;
        *child_type = -1;
    }
    else if ( strcmp(arg,"j") == 0 )
    {
        *parent_type = 6;
        *child_type = -1;
    }
    else if ( strcmp(arg,"k") == 0 )
    {
        *parent_type = 6;
        *child_type = -1;
    }
    else if ( strcmp(arg,"l") == 0 )
    {
        *parent_type = 7;
        *child_type = -1;
    }
    else if ( strcmp(arg,"m") == 0 )
    {
        *parent_type = 7;
        *child_type = -1;
    }
    else if ( strcmp(arg,"n") == 0 )
    {
        *parent_type = 8;
        *child_type = -1;
    }
    else if ( strcmp(arg,"o") == 0 )
    {
        *parent_type = 8;
        *child_type = -1;
    }
    else
    {
        printf("FATTREE_ERROR: Something went wrong.");
        exit(1);
    }

}

void execute_program(char filename[50])
{
    /*
      Creates new process to execute program
    */
    long pid;

    pid = fork();
    if ( pid < 0 )
    {
        printf("FATTREE_ERROR: fork failed.\n");
        exit(1);
    }

    /* Executing only in the new process */
    if ( pid == 0 )
    {
        if ( execl(filename, filename, (char*)0) < 1 )
        {
            //printf("FATTREE_ERROR: execl returned error.\n");
            exit(1);
        }
    }
}

void run_fattree(long parent_type, long child_type, int queue_tree_id, int queue_id)
{
    time_t start, end;
    double diff;
    message_t msg_rcv, msg_snd;
    char start_string[100], end_string[100], diff_string[100];
    int state;

    while( true )
    {   
        /* Receive message from parent */
        if ( parent_type == 1 )
        {
            receive_message(&msg_rcv, queue_id, parent_type);
        }
        else
        {
            receive_message(&msg_rcv, queue_tree_id, parent_type);
        }
        
        /* If node has children */
        if ( child_type != -1 )
        {
            /* Send message to one child */
            msg_snd.pid = child_type;
            strcpy(msg_snd.filename, msg_rcv.filename);
            send_message(msg_snd, queue_tree_id);

            /* Send message to other child */
            send_message(msg_snd, queue_tree_id);
        }

        /* Executing program in special node and counting the time taken */
        start = time(NULL);
        
        execute_program(msg_rcv.filename);
        wait(&state);
        
        end = time(NULL);
        diff = difftime(end, start);

        strcpy(msg_rcv.filename, "\0");
        strcpy(msg_snd.filename, "\0");

        /* If node has children */
        if ( child_type != -1 )
        {   
            /* Receive message from one child */
            receive_message(&msg_rcv, queue_tree_id, child_type);
            strcpy(msg_snd.filename, msg_rcv.filename);

            /* Receive message from other child */
            receive_message(&msg_rcv, queue_tree_id, child_type);
            strcat(msg_snd.filename, msg_rcv.filename);
        }

        /* Creating string with start and end times */
        // sprintf(start_string, "%f", start);
        // sprintf(end_string, "%f", end);
        // strcat(end_string, "\n");
        // strcat(start_string, " ");
        // strcat(start_string, end_string);
        sprintf(diff_string, "%f", diff);
        strcat(diff_string, "\n");

        /* Send message to parent */
        msg_snd.pid = parent_type;
        strcat(msg_snd.filename, diff_string);
        
        if ( parent_type == 1 )
        {
            send_message(msg_snd, queue_id);
        }
        else
        {
            send_message(msg_snd, queue_tree_id);
        }

        sleep(1);
    }
}

void main(int argc, char **argv)
{
    long pid;
    int queue_tree_id, queue_id, i;
    long parent_type, child_type;
    char *arg;

    pid = getpid();

    queue_tree_id = retrieve_queue_id(1);
    queue_id = retrieve_queue_id(0);

    strcpy(arg,argv[1]);
    setup_fattree(arg, &parent_type, &child_type);

    run_fattree(parent_type, child_type, queue_tree_id, queue_id);

    exit(0);
}