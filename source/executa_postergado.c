/*
 * Authors: 
 * André Luís Souto Ferreira 14/0016261
 * Otto Kristian von Sperling 12/0131510
 * Victor Fabre Figueiredo 15/0022948
 * 
 */

#include "data_structures.h"

/*
Data Structure for the message to be exchanged between the job_scheduler ('escalonador')
and the delay_execution ('executa_postergado') modules
*/
struct message
{
   long pid;
   char filename[500];
   unsigned int delta_delay;
};


/* -------------------------- DEFINITON OF METHODS --------------------------------------------- */
/*
Main methods
*/
int retrieve_queue_id();
bool send_message( message_t message_to_send, int queue_id );

/*
Auxiliary methods.
*/
const char * parse_clarg_filename(int argc, char *argv[]);
unsigned int parse_clarg_delay(int argc, char *argv[]);


/* ------------------------- IMPLEMENTATION OF METHODS ---------------------------------------- */
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

/*
Auxiliary methods for the delay_execution module ------------------------------------------------------
*/
const char * parse_clarg_filename( int argc, char *argv[] )
{
   /*
   Returns a string with the filename passed as an argument in the command line, exits if input is not found.
   */
   char * filename;
   extern int errno;

   for( int optindex = 1; optindex < argc; optindex++ )
   {
      // finds the '-f flag'
      if( argv[optindex][0] == '-' && argv[optindex][1] == 'f' )
      {
         filename = argv[optindex+1];

         // checks whether the file exists
         if( access(filename, F_OK) != -1 )
            return filename;
         
         // if the file does not exist, prints error and exits with the error code
         else
         {
            perror( "CL_PARSER_ERROR (filename)" );
            exit( errno );
         }
      }
   }

   // the '-f' flag was not found. Thus, prints error and exits
   printf( "CL_PARSER_ERROR: FlagError\n\tNo filename flag '-f' found.\n\tThe pattern < -f filename > must be followed\n" );
   exit(1);
      
}

unsigned int parse_clarg_delay(int argc, char *argv[])
{
   /*
   Returns an integer that represents the delay in seconds passed as an argument in the command line,
   exits if input is not found.
   */
   for( int optindex = 1; optindex < argc; optindex++ )
   {
      // finds the '-d' flag
      if( argv[optindex][0] == '-' && argv[optindex][1] == 'd' )
      {
         // checks if an argument was given after the flag
         if( optindex+1 >= argc )
         {
            printf("CL_PARSER_ERROR: ValueError\n\tThere is no argument for the '-d' flag.\n");
            exit(1);
         }

         // checks if the arg is digit
         if( strspn(argv[optindex+1], "0123456789") == strlen(argv[optindex+1]) )
         {
            size_t big_digit = 0;
            sscanf(argv[optindex+1], "%zu%*c",&big_digit);
            return (int)big_digit;   
         }

         else
         {
            printf("CL_PARSER_ERROR: TypeError\n\tThe argument for the '-d' flag must contain only digits.\n");
            exit(1);
         }
         
      }
   }

   // the '-f' flag was not found. Thus, prints error and exits
   printf( "CL_PARSER_ERROR: FlagError\n\tNo delay flag '-d' found."
           "\n\tThe pattern < -d delay (in seconds) > must be followed\n" );
   exit(1);
}

int main(int argc, char *argv[])
{
   // int fd[2];
   unsigned int queue_id;
   message_t message_to_send;

   message_to_send.pid = getpid();
   strcpy(message_to_send.filename, parse_clarg_filename(argc, argv));
   message_to_send.delta_delay = parse_clarg_delay(argc, argv);
   
   queue_id = retrieve_queue_id();
   if( send_message(message_to_send, queue_id) )
      printf("SUCCESS:"
             "\n\tFile '%s' successfully placed in the execution queue "
             "\n\t(minimum delay of %d seconds)\n",message_to_send.filename, message_to_send.delta_delay);

   exit(0);
}
