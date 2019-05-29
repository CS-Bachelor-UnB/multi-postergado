#include "torus.h"


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
	long can_acess_pid[4];
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

void ready_torus_cell(cell_t torus[16], int cell_num)
{
	switch(cell_num)
	{
		
		case 0:
			torus[0].can_acess_pos[0] = 12;
			torus[0].can_acess_pos[1] = 3;
			torus[0].can_acess_pos[2] = 1;
			torus[0].can_acess_pos[3] = 4;
			/*torus[cell_num].can_acess_pid[0] = torus[12].pid;
			torus[cell_num].can_acess_pid[1] = torus[3].pid;
			torus[cell_num].can_acess_pid[2] = torus[1].pid;
			torus[cell_num].can_acess_pid[3] = torus[4].pid;*/
			break;
		case 1:
			torus[0].can_acess_pos[0] = 13;
			torus[0].can_acess_pos[1] = 0;
			torus[0].can_acess_pos[2] = 2;
			torus[0].can_acess_pos[3] = 5;
			/*torus[cell_num].can_acess_pid[0] = torus[13].pid;
			torus[cell_num].can_acess_pid[1] = torus[0].pid;
			torus[cell_num].can_acess_pid[2] = torus[2].pid;
			torus[cell_num].can_acess_pid[3] = torus[5].pid;*/
			break;
		case 2:
			torus[0].can_acess_pos[0] = 14;
			torus[0].can_acess_pos[1] = 1;
			torus[0].can_acess_pos[2] = 3;
			torus[0].can_acess_pos[3] = 6;
			/*torus[cell_num].can_acess_pid[0] = torus[14].pid;
			torus[cell_num].can_acess_pid[1] = torus[1].pid;
			torus[cell_num].can_acess_pid[2] = torus[3].pid;
			torus[cell_num].can_acess_pid[3] = torus[6].pid;*/
			break;
		case 3:
			torus[0].can_acess_pos[0] = 15;
			torus[0].can_acess_pos[1] = 0;
			torus[0].can_acess_pos[2] = 2;
			torus[0].can_acess_pos[3] = 7;
			/*torus[cell_num].can_acess_pid[0] = torus[15].pid;
			torus[cell_num].can_acess_pid[1] = torus[0].pid;
			torus[cell_num].can_acess_pid[2] = torus[2].pid;
			torus[cell_num].can_acess_pid[3] = torus[7].pid;*/
			break;
		case 4:
			torus[0].can_acess_pos[0] = 0;
			torus[0].can_acess_pos[1] = 7;
			torus[0].can_acess_pos[2] = 5;
			torus[0].can_acess_pos[3] = 8;
			/*torus[cell_num].can_acess_pid[0] = torus[0].pid;
			torus[cell_num].can_acess_pid[1] = torus[7].pid;
			torus[cell_num].can_acess_pid[2] = torus[5].pid;
			torus[cell_num].can_acess_pid[3] = torus[8].pid;*/
			break;
		case 5:
			torus[0].can_acess_pos[0] = 1;
			torus[0].can_acess_pos[1] = 4;
			torus[0].can_acess_pos[2] = 6;
			torus[0].can_acess_pos[3] = 9;
			/*torus[cell_num].can_acess_pid[0] = torus[1].pid;
			torus[cell_num].can_acess_pid[1] = torus[4].pid;
			torus[cell_num].can_acess_pid[2] = torus[6].pid;
			torus[cell_num].can_acess_pid[3] = torus[9].pid;*/
			break;
		case 6:
			torus[0].can_acess_pos[0] = 2;
			torus[0].can_acess_pos[1] = 5;
			torus[0].can_acess_pos[2] = 7;
			torus[0].can_acess_pos[3] = 10;
			/*torus[cell_num].can_acess_pid[0] = torus[2].pid;
			torus[cell_num].can_acess_pid[1] = torus[5].pid;
			torus[cell_num].can_acess_pid[2] = torus[7].pid;
			torus[cell_num].can_acess_pid[3] = torus[10].pid;*/
			break;
		case 7:
			torus[0].can_acess_pos[0] = 3;
			torus[0].can_acess_pos[1] = 6;
			torus[0].can_acess_pos[2] = 4;
			torus[0].can_acess_pos[3] = 11;
			/*torus[cell_num].can_acess_pid[0] = torus[3].pid;
			torus[cell_num].can_acess_pid[1] = torus[6].pid;
			torus[cell_num].can_acess_pid[2] = torus[4].pid;
			torus[cell_num].can_acess_pid[3] = torus[11].pid;*/
			break;
		case 8:
			torus[0].can_acess_pos[0] = 4;
			torus[0].can_acess_pos[1] = 11;
			torus[0].can_acess_pos[2] = 9;
			torus[0].can_acess_pos[3] = 12;
			/*torus[cell_num].can_acess_pid[0] = torus[4].pid;
			torus[cell_num].can_acess_pid[1] = torus[11].pid;
			torus[cell_num].can_acess_pid[2] = torus[9].pid;
			torus[cell_num].can_acess_pid[3] = torus[12].pid;*/
			break;
		case 9:
			torus[0].can_acess_pos[0] = 5;
			torus[0].can_acess_pos[1] = 8;
			torus[0].can_acess_pos[2] = 10;
			torus[0].can_acess_pos[3] = 13;
			/*torus[cell_num].can_acess_pid[0] = torus[5].pid;
			torus[cell_num].can_acess_pid[1] = torus[8].pid;
			torus[cell_num].can_acess_pid[2] = torus[10].pid;
			torus[cell_num].can_acess_pid[3] = torus[13].pid;*/
			break;
		case 10:
			torus[0].can_acess_pos[0] = 6;
			torus[0].can_acess_pos[1] = 9;
			torus[0].can_acess_pos[2] = 11;
			torus[0].can_acess_pos[3] = 14;
			/*torus[cell_num].can_acess_pid[0] = torus[6].pid;
			torus[cell_num].can_acess_pid[1] = torus[9].pid;
			torus[cell_num].can_acess_pid[2] = torus[11].pid;
			torus[cell_num].can_acess_pid[3] = torus[14].pid;*/
			break;
		case 11:
			torus[0].can_acess_pos[0] = 7;
			torus[0].can_acess_pos[1] = 10;
			torus[0].can_acess_pos[2] = 8;
			torus[0].can_acess_pos[3] = 15;
			/*torus[cell_num].can_acess_pid[0] = torus[7].pid;
			torus[cell_num].can_acess_pid[1] = torus[10].pid;
			torus[cell_num].can_acess_pid[2] = torus[8].pid;
			torus[cell_num].can_acess_pid[3] = torus[15].pid;*/
			break;
		case 12:
			torus[0].can_acess_pos[0] = 8;
			torus[0].can_acess_pos[1] = 15;
			torus[0].can_acess_pos[2] = 13;
			torus[0].can_acess_pos[3] = 0;
			/*torus[cell_num].can_acess_pid[0] = torus[8].pid;
			torus[cell_num].can_acess_pid[1] = torus[15].pid;
			torus[cell_num].can_acess_pid[2] = torus[13].pid;
			torus[cell_num].can_acess_pid[3] = torus[0].pid;*/
			break;
		case 13:
			torus[0].can_acess_pos[0] = 9;
			torus[0].can_acess_pos[1] = 12;
			torus[0].can_acess_pos[2] = 14;
			torus[0].can_acess_pos[3] = 1;
			/*torus[cell_num].can_acess_pid[0] = torus[9].pid;
			torus[cell_num].can_acess_pid[1] = torus[12].pid;
			torus[cell_num].can_acess_pid[2] = torus[14].pid;
			torus[cell_num].can_acess_pid[3] = torus[1].pid;*/
			break;
		case 14:
			torus[0].can_acess_pos[0] = 10;
			torus[0].can_acess_pos[1] = 13;
			torus[0].can_acess_pos[2] = 15;
			torus[0].can_acess_pos[3] = 2;
			/*torus[cell_num].can_acess_pid[0] = torus[10].pid;
			torus[cell_num].can_acess_pid[1] = torus[13].pid;
			torus[cell_num].can_acess_pid[2] = torus[15].pid;
			torus[cell_num].can_acess_pid[3] = torus[1].pid;*/
			break;
		case 15:
			torus[0].can_acess_pos[0] = 11;
			torus[0].can_acess_pos[1] = 14;
			torus[0].can_acess_pos[2] = 12;
			torus[0].can_acess_pos[3] = 3;
			/*torus[cell_num].can_acess_pid[0] = torus[11].pid;
			torus[cell_num].can_acess_pid[1] = torus[14].pid;
			torus[cell_num].can_acess_pid[2] = torus[12].pid;
			torus[cell_num].can_acess_pid[3] = torus[3].pid;*/
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
            printf("TORUS_ERROR: execl returned error.\n");
            exit(1);
        }
    }
}

void run_torus(cell_t torus[], int queue_tree_id, int queue_id)
{
    clock_t start, end;
    message_t msg_rcv, msg_snd;
    float start_sec, end_sec;
    char start_string[100], end_string[100];
    int state, i;

    while( true )
    {   
        /* Receive message from parent */
        if (torus[0].my_pos == 0)
        {
            receive_message(&msg_rcv, queue_id, torus[0].my_pos);
        }
        else
        {
			receive_message(&msg_rcv, queue_tree_id, torus[0].my_pos);
        }
        
        
        for(i = 0; i < 4; i++)
        {
            /* Send message to one conection at a time */
            msg_snd.pid = torus[0].can_acess_pos[i];
            strcpy(msg_snd.filename, msg_rcv.filename);
            send_message(msg_snd, queue_tree_id);

        }

        /* Execute program in special node and count the time taken */
        start = clock();
        
        execute_program(msg_rcv.filename);
        wait(&state);
        
        end = clock();
        
        start_sec = (float)(start) / CLOCKS_PER_SEC;
        end_sec = (float)(end) / CLOCKS_PER_SEC;

        strcpy(msg_rcv.filename, "\0");
        strcpy(msg_snd.filename, "\0");

          
		/* Receive message from one conection */
		receive_message(&msg_rcv, queue_tree_id, torus[0].can_acess_pos[0]);
		strcpy(msg_snd.filename, msg_rcv.filename);
		/* Receive message from other conection */
		receive_message(&msg_rcv, queue_tree_id, torus[0].can_acess_pos[1]);
		strcat(msg_snd.filename, msg_rcv.filename);
		/* Receive message from other conection */
		receive_message(&msg_rcv, queue_tree_id, torus[0].can_acess_pos[2]);
		strcat(msg_snd.filename, msg_rcv.filename);
		/* Receive message from other conection */
		receive_message(&msg_rcv, queue_tree_id, torus[0].can_acess_pos[3]);
		strcat(msg_snd.filename, msg_rcv.filename);
        

        /* Creating string with start and end times */
        sprintf(start_string, "%f", start_sec);
        sprintf(end_string, "%f", end_sec);
        strcat(end_string, "\n");
        strcat(start_string, " ");
        strcat(start_string, end_string);

        /* Send message to parent */
        
        
        if (torus[0].my_pos == 0)
        {
            msg_snd.pid = torus[0].my_pos;
			strcat(msg_snd.filename, start_string);
            send_message(msg_snd, queue_id);
        }
        else
        {
            
            for(i = 0; i < 4; i++)
			{
				/* Send message to one conection at a time */
				msg_snd.pid = torus[0].can_acess_pos[i];
				strcat(msg_snd.filename, start_string);
				send_message(msg_snd, queue_tree_id);

			}

        }

        sleep(1);
    }
}

int main(int argc, char *argv[])
{

	cell_t torus[1];
	int i;
	long pid;
    int queue_torus_id, queue_id;
    char *arg;

    pid = getpid();

    queue_torus_id = retrieve_queue_id(1);
    queue_id = retrieve_queue_id(0);
    
    torus[0].my_pos = (int)argv[1][0]-48;
    ready_torus_cell(torus, (int)argv[1][0]-48);
    run_torus(torus, queue_torus_id, queue_id);
    //printf("%d:     %d %d %d %d\n\n", (int)argv[1][0]-48, torus[0].can_acess_pos[0], torus[0].can_acess_pos[1], torus[0].can_acess_pos[2], torus[0].can_acess_pos[3]);
	
	/*for(i = 0; i < 16; i++){
		
		torus[i].pid = i;
		ready_torus_cell(torus, (int)argv[1][0]-48);
		printf("%d %d %d %d\n\n", torus[0].can_acess_pos[0], torus[0].can_acess_pos[1], torus[0].can_acess_pos[2], torus[0].can_acess_pos[3]);	
		
	}

	/*for(i = 0; i < 16 ; i++){
		
		ready_torus_cell(torus, i);
		printf("%d %d %d %d\n%d %d %d %d\n\n", torus[i].can_acess_pos[0], torus[i].can_acess_pos[1], torus[i].can_acess_pos[2], torus[i].can_acess_pos[3],
											   torus[i].can_acess_pid[0], torus[i].can_acess_pos[1], torus[i].can_acess_pos[2], torus[i].can_acess_pos[3]);	
		
	} Just a test to see ir it is working properly.*/
	
	
	
	exit(0);
}

