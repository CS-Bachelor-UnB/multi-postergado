/*
 * Authors: 
 * André Luís Souto Ferreira 14/0016261
 * Otto Kristian von Sperling 12/0131510
 * Victor Fabre Figueiredo 15/0022948
 * 
 */

#include "data_structures.h"


/*
Data Structure for the message to be exchanged between the nodes of the torus
*/ 
struct message
{
   long pid;
   char filename[500];
   unsigned int delta_delay;
};

struct cell
{
	int my_pos;
	int can_acess_pos[4];
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
      return false;
   }

   else
      return true;
}

bool send_message( message_t message_to_send, int queue_id)
{
   /**/
   extern int errno;

   if( msgsnd( queue_id, &message_to_send, sizeof( message_to_send ) - sizeof( long ), 0 ) < 0 )
   {
      exit( errno );
   }

   else
      return true;
}

void ready_torus_cell(cell_t torus[16], int cell_num)
{
	/*Each node will receive a initial messagem from can_acess_pos[1] and pass to can_acess_pos[0]*/
	switch(cell_num)
	{
		
		case 0:
			torus[0].can_acess_pos[0] = 1;
			torus[0].can_acess_pos[1] = 3;
			torus[0].can_acess_pos[2] = 12;
			torus[0].can_acess_pos[3] = 4;
			
			break;
		case 1:
			torus[0].can_acess_pos[0] = 2;
			torus[0].can_acess_pos[1] = 0;
			torus[0].can_acess_pos[2] = 13;
			torus[0].can_acess_pos[3] = 5;
			
			break;
		case 2:
			torus[0].can_acess_pos[0] = 3;
			torus[0].can_acess_pos[1] = 1;
			torus[0].can_acess_pos[2] = 14;
			torus[0].can_acess_pos[3] = 6;
			
			break;
		case 3:
			torus[0].can_acess_pos[0] = 7;
			torus[0].can_acess_pos[1] = 2;
			torus[0].can_acess_pos[2] = 0;
			torus[0].can_acess_pos[3] = 15;
			
			break;
		case 4:
			torus[0].can_acess_pos[0] = 8;
			torus[0].can_acess_pos[1] = 5;
			torus[0].can_acess_pos[2] = 0;
			torus[0].can_acess_pos[3] = 7;
			
			break;
		case 5:
			torus[0].can_acess_pos[0] = 4;
			torus[0].can_acess_pos[1] = 6;
			torus[0].can_acess_pos[2] = 1;
			torus[0].can_acess_pos[3] = 9;
			
			break;
		case 6:
			torus[0].can_acess_pos[0] = 5;
			torus[0].can_acess_pos[1] = 7;
			torus[0].can_acess_pos[2] = 2;
			torus[0].can_acess_pos[3] = 10;
			
			break;
		case 7:
			torus[0].can_acess_pos[0] = 6;
			torus[0].can_acess_pos[1] = 3;
			torus[0].can_acess_pos[2] = 4;
			torus[0].can_acess_pos[3] = 11;
			
			break;
		case 8:
			torus[0].can_acess_pos[0] = 9;
			torus[0].can_acess_pos[1] = 4;
			torus[0].can_acess_pos[2] = 11;
			torus[0].can_acess_pos[3] = 12;
			
			break;
		case 9:
			torus[0].can_acess_pos[0] = 10;
			torus[0].can_acess_pos[1] = 8;
			torus[0].can_acess_pos[2] = 5;
			torus[0].can_acess_pos[3] = 13;
			
			break;
		case 10:
			torus[0].can_acess_pos[0] = 11;
			torus[0].can_acess_pos[1] = 9;
			torus[0].can_acess_pos[2] = 6;
			torus[0].can_acess_pos[3] = 14;
			
			break;
		case 11:
			torus[0].can_acess_pos[0] = 15;
			torus[0].can_acess_pos[1] = 10;
			torus[0].can_acess_pos[2] = 8;
			torus[0].can_acess_pos[3] = 7;
			
			break;
		case 12:
			torus[0].can_acess_pos[0] = 0;
			torus[0].can_acess_pos[1] = 13;
			torus[0].can_acess_pos[2] = 15;
			torus[0].can_acess_pos[3] = 0;
			
			break;
		case 13:
			torus[0].can_acess_pos[0] = 12;
			torus[0].can_acess_pos[1] = 14;
			torus[0].can_acess_pos[2] = 9;
			torus[0].can_acess_pos[3] = 1;
			
			break;
		case 14:
			torus[0].can_acess_pos[0] = 13;
			torus[0].can_acess_pos[1] = 15;
			torus[0].can_acess_pos[2] = 10;
			torus[0].can_acess_pos[3] = 2;
			
			break;
		case 15:
			torus[0].can_acess_pos[0] = 14;
			torus[0].can_acess_pos[1] = 11;
			torus[0].can_acess_pos[2] = 12;
			torus[0].can_acess_pos[3] = 3;
			
			break;	
		
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
        printf("TORUS_ERROR: fork failed.\n");
        exit(1);
    }

    /* Executing only in the new process */
    if ( pid == 0 )
    {
        if ( execl(filename, filename, (char*)0) < 1 )
        {
            exit(1);
        }
    }
}

void run_torus(cell_t torus[], int queue_torus_id, int queue_id)
{

    time_t start, end;
    double diff;
    message_t msg_rcv, msg_snd;
    char diff_string[100];
    int state;

    while( true )
    {   
        /* Receive message from parent */
        if (torus[0].my_pos == 0)
        {
            receive_message(&msg_rcv, queue_id, torus[0].my_pos+1);
        }
        else
        {
			receive_message(&msg_rcv, queue_torus_id, torus[0].my_pos+1);
        }
        
        
        if(torus[0].my_pos != 12)
        {
            /* Send message to one conection at a time */
            msg_snd.pid = torus[0].can_acess_pos[0]+1;
            strcpy(msg_snd.filename, msg_rcv.filename);
            send_message(msg_snd, queue_torus_id);

        }

        /* Executing program in special node and count the time taken */
        start = time(NULL);
        
        execute_program(msg_rcv.filename);
        wait(&state);
        
        end = time(NULL);

        diff = difftime(end, start);

        strcpy(msg_rcv.filename, "\0");
        strcpy(msg_snd.filename, "\0");

        
        if(torus[0].my_pos != 12)
        {
			receive_message(&msg_rcv, queue_torus_id, torus[0].can_acess_pos[0]+1);
			strcpy(msg_snd.filename, msg_rcv.filename);
		}
                  

        /* Creating string with start and end times */
        sprintf(diff_string, "%f", diff);
        strcat(diff_string, "\n");

        /* Send message to parent */
        msg_snd.pid = torus[0].my_pos+1;
		strcat(msg_snd.filename, diff_string);
        
        if (torus[0].my_pos == 0)
        {
            send_message(msg_snd, queue_id);
        }
        else
        {
            send_message(msg_snd, queue_torus_id);
        }

        sleep(1);
    }
}

int main(int argc, char *argv[])
{

	cell_t torus[1];
    int queue_torus_id, queue_id;


    queue_torus_id = retrieve_queue_id(1);
    queue_id = retrieve_queue_id(0);
    
    torus[0].my_pos = (int)argv[1][0]-48;
    ready_torus_cell(torus, (int)argv[1][0]-48);

    run_torus(torus, queue_torus_id, queue_id);
    
	
	
	exit(0);
}

