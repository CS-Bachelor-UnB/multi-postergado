#include "escalonador.h"
#define TIME_OUT 100

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

struct execution_entry
{
   char *filename;
   unsigned int delay;
   execution_entry_t *next;
};

struct execution_queue
{
   /*
      single-linked list
   */
   unsigned int len;
   execution_entry_t *head;
};

/*
Single-linked list methods for the delay_execution module ------------------------------------------------------
*/
execution_entry_t * createEntry(const char *filename, unsigned int delay)
{
   /* 
   Returns pointer to the new created entry of the single-linked list 
   */
   execution_entry_t *temp; 
   
   temp = (execution_entry_t *) malloc(sizeof(execution_entry_t));
   temp->filename = (char*) filename;
   temp->delay = delay;
   temp->next = NULL;
   
   return temp;
}

execution_queue_t * createLinkedList()
{
   /* 
   Returns pointer to the new created single-linked list 
   */
   execution_queue_t *list; 
   
   list = (execution_queue_t *) malloc(sizeof(execution_queue_t));
   list->len = 0;
   list->head = NULL;
   
   return list;
}

int addEntry(execution_entry_t * entry, execution_queue_t * list)
{
   /* 
   Returns 0 if adding to the list was successfull, and -1 if it fails
   */
   if ( list->len == 0 )
   {
     list->head = entry;
     list->len++;
     
     return 0;
   }
   
   execution_entry_t *aux = list->head;
   execution_entry_t *aux_b = list->head;
   
   while ( aux != NULL )
   {
     if ( aux->delay > entry->delay )
     {
       if (aux == aux_b)
       {
         list->head = entry;
         entry->next = aux;
       }
       else
       {
         aux_b->next = entry;
         entry->next = aux;
       }
       
       list->len++;
       return 0;
     }

     aux_b = aux;
     aux = aux->next;

     if ( aux == NULL )
     {
       aux_b->next = entry;
       entry->next = NULL;
       
       list->len++;
       return 0;
     }
   }

   return -1;

}

int removeEntry(execution_entry_t * entry, execution_queue_t *list)
{
   /* 
   Returns 0 if removing from list was successfull, and -1 if it fails
   */
   if ( list->len == 0 )
   {
     return -1;
   }
   
   execution_entry_t *aux = list->head;
   execution_entry_t *aux_b = list->head;
   
   if ( (list->len - 1) == 0 )
   {
     list->head = NULL;
   }

   while ( aux != NULL )
   {
     if ( aux == entry )
     {
       if (aux == aux_b)
       {
         list->head = entry->next;
         entry->next = NULL;
       }
       else
       {
         aux_b->next = entry->next;
         entry->next = NULL;
       }
       
       free(entry);
       list->len--;
       return 0;
     }

     aux_b = aux;
     aux = aux->next;
   }

   return -1;
}

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
      return false;
      //exit( errno );
   }

   else
      return true;
}

/*
Auxiliary methods for the delay_execution module ------------------------------------------------------
*/

static void alarm_handler(int signo)
{
   printf("Caught a signal to delay\n");
   
   // TODO:
   // FatTree call
   // HyperCube call
   // The other one call

   flag = 1;

   //exit(EXIT_SUCCESS);
}

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
   message_t message_received;
   execution_queue_t * exec_queue = createLinkedList();
   unsigned int queue_id, previous_timer;

   signal(SIGALRM, alarm_handler);
   topology = parse_clarg_topology(argc, argv);
   queue_id = retrieve_queue_id();
   
   while(true)
   {
     if( receive_message( &message_received, queue_id ) )
     {
        printf("SUCCESS:"
              "\n\tFile '%s' successfully loaded from the execution queue "
              "\n\t(minimum delay of %d seconds)\n",message_received.filename,
              message_received.delta_delay);

        // now we add the new entry to the execution queue
        if( ( exec_queue->len > 0 ) && ( previous_timer = alarm( TIME_OUT ) > 0 ) )
        {
          /*
              if the execution_queue is not empty and there is a timer in countdown
          */
          if( previous_timer > message_received.delta_delay )
          {
              /*
                check if the delay for the new entry is smaller than the current one (already in countdown)
                if so,   i) set the new entry as the new head;
                          ii) set the remaining delay of the previous_timer;
                          iii) fire the alarm with the delay of the new head;
                !!! we will always assume the execution queue is sorted (MAKE SURE IT IS) !!!
              */
              exec_queue->head->delay = previous_timer;

              execution_entry_t *new_entry = createEntry(message_received.filename,
                                                        message_received.delta_delay);    
              if ( addEntry(new_entry, exec_queue) < 0 )
              {
                printf("FAILED: Adding new entry to linked-list\n");
              }

              alarm(message_received.delta_delay);
          }

          else
          {
              /* 
                if the delay for the new entry is bigger or equal to the current one (already in countdown)
                    i) refire the previous_timer
                    ii) add the new entry into place (SORTED!),
              */
              alarm(previous_timer);

              execution_entry_t *new_entry = createEntry(message_received.filename,
                                                        message_received.delta_delay);
              if( addEntry(new_entry, exec_queue) < 0 )
              {
                printf("FAILED: Adding new entry to linked-list\n");
              }
          } 
        }

        else if ( exec_queue->len == 0 )
        {
          /*
              no other process is waiting in the execution_queue
              add the new entry
          */
            execution_entry_t *new_entry = createEntry(message_received.filename,
                                                      message_received.delta_delay);    
            if ( addEntry(new_entry, exec_queue) < 0 )
            {
              printf("FAILED: Adding new entry to linked-list\n");
            }

            previous_timer = message_received.delta_delay;
            alarm(message_received.delta_delay);
        }

        else
        {
          /* !! if this part is reached, it's likely that there has been some sort of unwanted behavior !! */
        }
      }

      if ( flag == 1 )
      {
        /* 
          Accessed to get next program and delay from the current
          linked list
        */
        removeEntry(exec_queue->head, exec_queue);  
        if ( exec_queue->len > 0 )
        {
          alarm(exec_queue->head->delay);
        }

        flag = 0;
      }
   }
}