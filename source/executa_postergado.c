#include "executa_postergado.h"

#define file_pos 1
#define delay_pos 2

/*
Data Structure for the message to be exchanged between the job_scheduler ('escalonador')
and the delay_execution ('executa_postergado') modules
*/
struct message
{
   long pid;
   char * filename;
   int delta_delay;
};


/*
Auxiliary methods for the delay_execution module ------------------------------------------------------
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

   if (( queue_id = msgget( 0x1200, (IPC_CREAT|0x1B6) ) ) < 0)
   {
     printf( "Error while retrieving the queue_id\n" );
     return 0;
   }

   else
      return queue_id;
}

char * parse_clarg_filename( int argc, char *argv[] )
{
   /*
   Returns a string with the filename passed as an argument in the command line, exits if input is not found.
   FUTURE feature:
      + suggests files in the project examples folder, exits after a number of failed attempts.
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
            perror( "Error while parsing the filename argument" );
            exit( errno );
         }
      }
   }

   // the '-f' flag was not found. Thus, prints error and exits
   printf( "\nNo filename flag '-f' found. The pattern < -f filename > must be followed\n" );
   exit(1);
      
}

const int parse_clarg_delay(int argc, char *argv[])
{
   /*
   Returns an integer that represents the delay in seconds passed as an argument in the command line,
   exits if input is not found.
   FUTURE feature:
      + sets a default delay if none given.
   */
   for( int optindex = 1; optindex < argc; optindex++ )
   {
      // finds the '-d' flag
      if( argv[optindex][0] == '-' && argv[optindex][1] == 'd' )
      {

         // checks if the arg is digit
         if( strspn(argv[optindex+1], "0123456789") == strlen(argv[optindex+1]) )
         {
            size_t big_digit = 0;
            sscanf(argv[optindex+1], "%zu%*c",&big_digit);
            return (int)big_digit;   
         }

         else
         {
            printf("\nCL_PARSER_ERROR: TypeError\n\tThe argument for the '-d' flag must contain only digits.\n");
         }
         
      }
   }

   // the '-f' flag was not found. Thus, prints error and exits
   printf( "\nCL_PARSER_ERROR: FlagError\n\tNo delay flag '-d' found.\n\tThe pattern < -d delay (in seconds) > must be followed\n" );
   exit(1);
}

int main(int argc, char *argv[])
{
   // int queue_id, fd[2];
   message_t message_send; 

   message_send.filename = parse_clarg_filename(argc, argv);
   message_send.delta_delay = parse_clarg_delay(argc, argv);
   
   // while(true)
   //    if(queue_id = retrieve_queue_id() > 0)
   //       break;

   printf("\nOK!\n");

   exit(0);
}
/*  
   pid = fork();

   if (pid == 0)
   {
   mensagem_env.pid = getpid();
   strcpy(mensagem_env.msg, "teste de mensagem");
   msgsnd(queue_id, &mensagem_env, sizeof(mensagem_env)-sizeof(long), 0);
   exit (0);
   }
   msgsnd(queue_id, &message_send, sizeof(message_send)-sizeof(long), 0);      
   msgrcv(queue_id, &mensagem_rec, sizeof(mensagem_rec)-sizeof(long), 0, 0);
   printf("mensagem recebida = %ld %s\n", mensagem_rec.pid, mensagem_rec.msg);
   // wait(&estado);
*/