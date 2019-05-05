#include "escalonador.h"

/*
Data Structure for the message to be exchanged between the job_scheduler ('escalonador')
and the delay_execution ('executa_postergado') modules
*/ 
struct message
{
   long pid;
   const char filename[50];
   unsigned int delta_delay;
};

/*
Main methods for the delay_execution module ------------------------------------------------------
*/
int retrieve_queue_id()
{
   /*
   Returns a standard queue_id shared with  the job_scheduler or zero in case it fails
   FUTURE feature:
      + send interrupt signal to the job_scheduler to retrieve the current queue_id
        (and to let it know that a new job request has arrived).
        The interruption must be treated in the job_scheduler module.
   */
   int queue_id;
   extern int errno;

   if ( ( queue_id = msgget( 0x1200, (IPC_CREAT|0x1B6 ) ) ) < 0 )
   {
     perror( "\nRETRIEVE_QUEUE_ERROR: Error while retrieving the queue_id\n" );
     exit( errno );
   }

   else
      return queue_id;
}

bool receive_message( message_t *message_received, int queue_id )
{
   /**/
   extern int errno;

   if( msgrcv( queue_id, message_received, sizeof( *message_received ) - sizeof( long ), 0, MSG_NOERROR ) < 0 )
   {
      // prints error message
      perror("RECEIVE_MESSAGE_ERROR");
      exit( errno );
   }

   else
      return true;
}

int main( int argc, char *argv[] )
{
    message_t message_received;
    unsigned int queue_id;

    queue_id = retrieve_queue_id();
    if( receive_message( &message_received, queue_id ) )
        printf("SUCCESS:"
             "\n\tFile '%s' successfully loaded from the execution queue "
             "\n\t(minimum delay of %d seconds)\n",message_received.filename,
             message_received.delta_delay);
}