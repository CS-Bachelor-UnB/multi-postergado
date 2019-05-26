#include "fattree.h"

/*
Data Structure for the message to be exchanged between the nodes of the fat tree
*/ 
struct message
{
   long pid;
   char filename[50];
   unsigned int delta_delay;
};

int retrieve_queue_id()
{
   /*
   Returns a standard queue_id shared with  the job_scheduler or zero in case it fails
   */
   int queue_id;
   extern int errno;

   if ( ( queue_id = msgget( 0x6261, (IPC_CREAT|0x1B6 ) ) ) < 0 )
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
      perror("RECEIVE_MESSAGE_ERROR");
      
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
      perror("SEND_MESSAGE_ERROR");
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
            printf("FATTREE_ERROR: execl returned error.\n");
            exit(1);
        }
    }
}

void run_fattree(long parent_type, long child_type, int queue_id)
{
    message_t msg_rcv, msg_snd;
    int state;

    while( true )
    {   
        /* Receive message from parent */
        receive_message(&msg_rcv, queue_id, parent_type);
        
        /* If node has children */
        if ( child_type != -1 )
        {
            /* Send message to one child */
            msg_snd.pid = child_type;
            strcpy(msg_snd.filename, msg_rcv.filename);
            send_message(msg_snd, queue_id);

            /* Send message to other child */
            msg_snd.pid = child_type;
            strcpy(msg_snd.filename, msg_rcv.filename);
            send_message(msg_snd, queue_id);
        }

        /* Execute program in special node */
        execute_program(msg_rcv.filename);
        wait(&state);

        // if ( child_type != -1 )
        // {   
        //     /* Receive message from one child */
        //     receive_message();

        //     /* Receive message from other child */
        //     receive_message();
        // }

        /* Send message to parent */
        //send_message();
    }

}

void main(int argc, char **argv)
{
    long pid;
    int queue_id, i;
    long parent_type, child_type;
    char *arg;

    pid = getpid();

    queue_id = retrieve_queue_id();

    strcpy(arg,argv[1]);
    setup_fattree(arg, &parent_type, &child_type);

    run_fattree(parent_type, child_type, queue_id);

    exit(0);
}