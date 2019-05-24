#include "fattree.h"

/*
Data Structure for the message to be exchanged between the nodes of the fat tree
*/ 
struct message
{
   long pid;
   const char filename[50];
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

void main(int argc, char **argv)
{
    long pid;
    int queue_id, i;
    long parent_type, child_type;

    pid = getpid();

    queue_id = retrieve_queue_id();

    /* 
       Obtaining types to be used when sending and receiving 
       messages with message queue
    */
    if ( strcmp(argv[1],"a") == 0 )
    {
        parent_type = 1;
        child_type = 2;
    }
    else if ( strcmp(argv[1],"b") == 0 )
    {
        parent_type = 2;
        child_type = 3;
    }
    else if ( strcmp(argv[1],"c") == 0 )
    {
        parent_type = 2;
        child_type = 4;
    }
    else if ( strcmp(argv[1],"d") == 0 )
    {
        parent_type = 3;
        child_type = 5;
    }
    else if ( strcmp(argv[1],"e") == 0 )
    {
        parent_type = 3;
        child_type = 6;
    }
    else if ( strcmp(argv[1],"f") == 0 )
    {
        parent_type = 4;
        child_type = 7;
    }
    else if ( strcmp(argv[1],"g") == 0 )
    {
        parent_type = 4;
        child_type = 8;
    }
    else if ( strcmp(argv[1],"h") == 0 )
    {
        parent_type = 5;
        child_type = -1;
    }
    else if ( strcmp(argv[1],"i") == 0 )
    {
        parent_type = 5;
        child_type = -1;
    }
    else if ( strcmp(argv[1],"j") == 0 )
    {
        parent_type = 6;
        child_type = -1;
    }
    else if ( strcmp(argv[1],"k") == 0 )
    {
        parent_type = 6;
        child_type = -1;
    }
    else if ( strcmp(argv[1],"l") == 0 )
    {
        parent_type = 7;
        child_type = -1;
    }
    else if ( strcmp(argv[1],"m") == 0 )
    {
        parent_type = 7;
        child_type = -1;
    }
    else if ( strcmp(argv[1],"n") == 0 )
    {
        parent_type = 8;
        child_type = -1;
    }
    else if ( strcmp(argv[1],"o") == 0 )
    {
        parent_type = 8;
        child_type = -1;
    }
    else
    {
        printf("FATTREE_ERROR: Something went wrong.");
        exit(1);
    }

    while( true )
    {



    }
}