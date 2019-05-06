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

/*
Auxiliary methods for the delay_execution module ------------------------------------------------------
*/

bool contains_string( const char ** array, int array_size, char * string )
{
   /**/
   for( int i = 0; i < array_size; i++ )
      if( !strcmp(array[i], string ) )
         return true;
      
   return false;
         
}

const char * parse_clarg_topology( int argc, char *argv[] )
{
   /*
   Returns a string with the filename passed as an argument in the command line, exits if input is not found.
   FUTURE feature:
      + suggests files in the project examples folder, exits after a number of failed attempts.
   */
   char * topology;
   const char * possible_topologies[3] = {"fattree", "torus", "hypercube"};

   for( int optindex = 1; optindex < argc; optindex++ )
   {
      // finds the '-f flag'
      if( argv[optindex][0] == '-' && argv[optindex][1] == 't' )
      {
         if( optindex+1 >= argc )
         {
            printf("CL_PARSER_ERROR: ValueError\n\tThere is no argument for the '-t' flag.\n");
            exit(1);
         }

         topology = argv[optindex+1];

         // checks whether the file exists
         if( contains_string(possible_topologies, 3, topology) )
            return topology;
         
         // if the file does not exist, prints error and exits with the error code
         else
         {
            printf( "CL_PARSER_ERROR (topology): topology '%s' not supported\n", topology );
            exit(1);
         }
      }
   }

   // the '-f' flag was not found. Thus, prints error and exits
   printf( "CL_PARSER_ERROR: FlagError\n\tNo TOPOLOGY_FLAG '-t' found.\n\tThe pattern < -t topology > must be followed\n" );
   exit(1);
      
}


int main( int argc, char *argv[] )
{
   unsigned int queue_id;
   const char * topology;
   message_t message_received;

   topology = parse_clarg_topology(argc, argv);
   queue_id = retrieve_queue_id();
   
   if( receive_message( &message_received, queue_id ) )
      printf("SUCCESS:"
             "\n\tFile '%s' successfully loaded from the execution queue "
             "\n\t(minimum delay of %d seconds)\n",message_received.filename,
             message_received.delta_delay);
}