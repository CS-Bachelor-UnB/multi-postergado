#include "escalonador.h"
#define TIME_OUT 100

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

struct execution_entry
{
   int job;
   char filename[500];
   unsigned int delay;
   float makespan;
   execution_entry_t *next;
};

struct execution_queue
{
   /*
     Single-linked list
   */
   unsigned int len;
   execution_entry_t *head;
};

/*
Single-linked list methods for the delay_execution module ------------------------------------------------------
*/
execution_entry_t * createEntry(char filename[500], unsigned int delay)
{
   /* 
     Returns pointer to the new created entry of the single-linked list 
   */
   execution_entry_t *temp; 
   
   temp = (execution_entry_t *) malloc(sizeof(execution_entry_t));
   strcpy(temp->filename, filename);
   temp->delay = delay;
   temp->makespan = 0.0;
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

int addEntryToHead(execution_entry_t * entry, execution_queue_t * list)
{
   /* 
     Returns 0 if adding to the list was successfull, and -1 if it fails.
     New entry is added to the head of the linked list.
   */
  execution_entry_t *auxiliar;

  auxiliar = list->head;
  list->head = entry;
  entry->next = auxiliar;

  list->len++;

  return 0;
}

int addEntry(execution_entry_t * entry, execution_queue_t * list)
{
   /* 
     Returns 0 if adding to the list was successfull, and -1 if it fails
   */

   /* If linked list is empty */
   if ( list->len == 0 )
   {
     list->head = entry;
     list->len++;
     
     return 0;
   }
   
   /* If linked list is not empty */
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
   /* If linked list is empty */
   if ( list->len == 0 )
   {
     return -1;
   }
   
   /* If linked list is not empty */
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
int retrieve_queue_id(int type)
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
      perror("SEND_MESSAGE_ERROR");
      exit( errno );
   }

   else
      return true;
}

/*
Auxiliary methods for the delay_execution module ------------------------------------------------------
*/

static void create_processes(const char * topology)
{
  /* 
    Creates 15 processes and put them into a specified topology  
  */
  int pid, i;
  char exec_argv[1];

  for( i = 0; i < 15; i++ )
   { 
      pid = fork();
      if ( pid < 0 )
      {
        printf("PROCESS_CREATION_ERROR: fork returned -1.\n");
        exit(1);
      }
      else if( pid > 0 )
      {
        process_pid[i] = pid;
      }

      if( pid == 0 && strcmp(topology,"fattree") == 0 )
      { 
         
         exec_argv[0] = 97 + i;

         if ( execl("fattree", "fattree", exec_argv, (char *)0) < 1 )
         {
           printf("PROCESS_CREATION_ERROR: execl failed.\n");
           exit(1);
         }
      }
      else if( pid == 0 && strcmp(topology,"hypercube") == 0 )
      {
        // TODO: hypercube call
      }
      else if( pid == 0 && strcmp(topology,"torus") == 0 )
      {
        // TODO: torus call
      }
      else if ( pid == 0 )
      {
          printf("TOPOLOGY_ERROR: invalid topology.\n");
          exit(1);
      }
   }
}

static void alarm_handler(int signo)
{
   /*
    When an alarm rings, it should be checked if the manager processess are
    availabled, if they are, send a message with the next file to be executed
   */
   char filename[50];
   unsigned int delay;
   execution_entry_t *new_entry;
   int queue_id;
   message_t msg;
   
  //  /* Busy waiting until manager processes are available */
  //  while( busy != 0 ){;}
   
   strcpy(filename, exec_queue->head->filename);
   delay = exec_queue->head->delay;
   
   new_entry = createEntry(filename,delay);
   new_entry->job = exec_queue->head->job;

   /* Updating linked-lists */
   if ( addEntryToHead(new_entry, exec_queue_done) < 0 )
   {
     printf("LINKED_LIST_ERROR: Adding new entry to linked-list of done jobs failed\n");
   }
  
   queue_id = retrieve_queue_id(0);
   msg.pid = 1;
   strcpy(msg.filename, filename);
   msg.delta_delay = 0;
   send_message(msg,queue_id);

   removeEntry(exec_queue->head, exec_queue); 

   busy = 1;

   /* Gets next program and delay from linked list */ 
   if ( exec_queue->len > 0 )
   {
     alarm(exec_queue->head->delay);
   }
}

void print_statistics()
{
    /*
      Showing info of all executed processes
    */
    execution_entry_t * aux;
    int i;

    aux = exec_queue_done->head;
    printf("\nINFO STATISTICS: \n\n");

    for ( i == 0; i < exec_queue_done->len; i++)
    {
      printf("Job number %d "
            "\nFile '%s' "
            "\nDelay %d seconds"
            "\nMakespan %.2f seconds\n", aux->job,
                                       aux->filename,
                                       aux->delay,
                                       aux->makespan);
      aux = aux->next;
    }
}

static void process_shutdown(int signo)
{
   /*
    Shutdown all processes and removes all message queues after
    a SIGUSR1 from terminal
   */
   printf("\nSHUTTING DOWN MESSAGE QUEUES AND PROCESSES !\n");

   int pid, queue_id, i, state;;
   
   pid = fork();

   if ( pid > 0 )
   {  
      queue_id = retrieve_queue_id(0);
      msgctl(queue_id, IPC_RMID, 0);

      queue_id = retrieve_queue_id(1);
      msgctl(queue_id, IPC_RMID, 0);

      if ( exec_queue->len > 0 )
      {
        printf("PROCESS_SHUTDOWN: Processes present in the execution queue won't be executed.\n");
      }

      print_statistics();

      for ( i = 0; i < 15; i++ )
      {
        if ( kill(process_pid[i], SIGKILL) != 0 )
        {
          printf("PROCESS_SHUTDOWN_ERROR: Kill did not return 0. Something went wrong.\n");
        }
      }
   }

   wait(&state);
   exit(0);

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
   const char * topology;
   message_t message_received;
   unsigned int queue_id, previous_timer;
   int unique_job = 1;
   double makespan = 0.0;

   exec_queue = createLinkedList();
   exec_queue_done = createLinkedList();
   
   signal(SIGUSR1, process_shutdown);
   signal(SIGALRM, alarm_handler);
   
   topology = parse_clarg_topology(argc, argv);
   queue_id = retrieve_queue_id(0);
    
   create_processes(topology);
   
   while(true)
   {
     if( receive_message( &message_received, queue_id, 0 ) )
     {
       /* If message received comes from the manager process */
       if ( message_received.pid == 1 )
       {
         char makespan [10];
         int i = 0;
         
         while ( message_received.filename[i] != '\n' )
         {
           makespan[i] = message_received.filename[i];
           i++;
         }
         
         exec_queue_done->head->makespan = atof(makespan);
         
         printf("\nSUCCESS: Done execution."
                "\nJob number %d "
                "\nFile '%s' "
                "\nDelay %d seconds"
                "\nMakespan %.2f seconds\n", exec_queue_done->head->job,
                                             exec_queue_done->head->filename,
                                             exec_queue_done->head->delay,
                                             exec_queue_done->head->makespan);
       }
       /* If message received comes from executa_postergado */
       else
       {
          printf("SUCCESS:"
                "\n\tFile '%s' successfully loaded from the execution queue "
                "\n\t(minimum delay of %d seconds)\n",message_received.filename,
                message_received.delta_delay);

          // now we add the new entry to the execution queue
          if( ( exec_queue->len > 0 ) && ( (previous_timer = alarm( TIME_OUT )) > 0 ) )
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
                new_entry->job = unique_job;
                unique_job++;   
                
                if ( addEntry(new_entry, exec_queue) < 0 )
                {
                  printf("LINKED_LIST_ERROR: Adding new entry to linked-list failed\n");
                }

                alarm(message_received.delta_delay);
            }

            else
            {
                /* 
                  if the delay for the new entry is bigger or equal to the current one (already in countdown)
                      i) update time left of the linked list's first entry;
                      ii) refire the previous_timer;
                      iii) add the new entry into place (SORTED!).
                */
                exec_queue->head->delay = previous_timer;
                alarm(previous_timer);

                execution_entry_t *new_entry = createEntry(message_received.filename,
                                                           message_received.delta_delay);
                new_entry->job = unique_job;
                unique_job++;

                if( addEntry(new_entry, exec_queue) < 0 )
                {
                  printf("LINKED_LIST_ERROR: Adding new entry to linked-list failed\n");
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
              new_entry->job = unique_job;
              unique_job++;
              
              if ( addEntry(new_entry, exec_queue) < 0 )
              {
                printf("LINKED_LIST_ERROR: Adding new entry to linked-list failed\n");
              }

              alarm(message_received.delta_delay);
          }

          else
          {
            /* !! if this part is reached, it's likely that there has been some sort of unwanted behavior !! */
          }
        }
      }

      // if ( flag == 1 )
      // {
      //   /* 
      //     Gets next program and delay from linked list.
      //   */ 
      //   if ( exec_queue->len > 0 )
      //   {
      //     alarm(exec_queue->head->delay);
      //   }

      //   flag = 0;
      // }
   }
}