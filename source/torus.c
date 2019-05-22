#include "torus.h"

struct message
{
   long pid;
   const char text[50];
   unsigned int t;
};

struct cell
{
	long pid;
	int can_acess_pos[4];
	long can_acess_pid[4];
};

void ready_torus_cell(cell_t torus[16], int cell_num)
{
	switch(cell_num)
	{
		
		case 0:
			torus[cell_num].can_acess_pos[0] = 12;
			torus[cell_num].can_acess_pos[1] = 3;
			torus[cell_num].can_acess_pos[2] = 1;
			torus[cell_num].can_acess_pos[3] = 4;
			torus[cell_num].can_acess_pid[0] = torus[12].pid;
			torus[cell_num].can_acess_pid[1] = torus[3].pid;
			torus[cell_num].can_acess_pid[2] = torus[1].pid;
			torus[cell_num].can_acess_pid[3] = torus[4].pid;
			break;
		case 1:
			torus[cell_num].can_acess_pos[0] = 13;
			torus[cell_num].can_acess_pos[1] = 0;
			torus[cell_num].can_acess_pos[2] = 2;
			torus[cell_num].can_acess_pos[3] = 5;
			torus[cell_num].can_acess_pid[0] = torus[13].pid;
			torus[cell_num].can_acess_pid[1] = torus[0].pid;
			torus[cell_num].can_acess_pid[2] = torus[2].pid;
			torus[cell_num].can_acess_pid[3] = torus[5].pid;
			break;
		case 2:
			torus[cell_num].can_acess_pos[0] = 14;
			torus[cell_num].can_acess_pos[1] = 1;
			torus[cell_num].can_acess_pos[2] = 3;
			torus[cell_num].can_acess_pos[3] = 6;
			torus[cell_num].can_acess_pid[0] = torus[14].pid;
			torus[cell_num].can_acess_pid[1] = torus[1].pid;
			torus[cell_num].can_acess_pid[2] = torus[3].pid;
			torus[cell_num].can_acess_pid[3] = torus[6].pid;
			break;
		case 3:
			torus[cell_num].can_acess_pos[0] = 15;
			torus[cell_num].can_acess_pos[1] = 0;
			torus[cell_num].can_acess_pos[2] = 2;
			torus[cell_num].can_acess_pos[3] = 7;
			torus[cell_num].can_acess_pid[0] = torus[15].pid;
			torus[cell_num].can_acess_pid[1] = torus[0].pid;
			torus[cell_num].can_acess_pid[2] = torus[2].pid;
			torus[cell_num].can_acess_pid[3] = torus[7].pid;
			break;
		case 4:
			torus[cell_num].can_acess_pos[0] = 0;
			torus[cell_num].can_acess_pos[1] = 7;
			torus[cell_num].can_acess_pos[2] = 5;
			torus[cell_num].can_acess_pos[3] = 8;
			torus[cell_num].can_acess_pid[0] = torus[0].pid;
			torus[cell_num].can_acess_pid[1] = torus[7].pid;
			torus[cell_num].can_acess_pid[2] = torus[5].pid;
			torus[cell_num].can_acess_pid[3] = torus[8].pid;
			break;
		case 5:
			torus[cell_num].can_acess_pos[0] = 1;
			torus[cell_num].can_acess_pos[1] = 4;
			torus[cell_num].can_acess_pos[2] = 6;
			torus[cell_num].can_acess_pos[3] = 9;
			torus[cell_num].can_acess_pid[0] = torus[1].pid;
			torus[cell_num].can_acess_pid[1] = torus[4].pid;
			torus[cell_num].can_acess_pid[2] = torus[6].pid;
			torus[cell_num].can_acess_pid[3] = torus[9].pid;
			break;
		case 6:
			torus[cell_num].can_acess_pos[0] = 2;
			torus[cell_num].can_acess_pos[1] = 5;
			torus[cell_num].can_acess_pos[2] = 7;
			torus[cell_num].can_acess_pos[3] = 10;
			torus[cell_num].can_acess_pid[0] = torus[2].pid;
			torus[cell_num].can_acess_pid[1] = torus[5].pid;
			torus[cell_num].can_acess_pid[2] = torus[7].pid;
			torus[cell_num].can_acess_pid[3] = torus[10].pid;
			break;
		case 7:
			torus[cell_num].can_acess_pos[0] = 3;
			torus[cell_num].can_acess_pos[1] = 6;
			torus[cell_num].can_acess_pos[2] = 4;
			torus[cell_num].can_acess_pos[3] = 11;
			torus[cell_num].can_acess_pid[0] = torus[3].pid;
			torus[cell_num].can_acess_pid[1] = torus[6].pid;
			torus[cell_num].can_acess_pid[2] = torus[4].pid;
			torus[cell_num].can_acess_pid[3] = torus[11].pid;
			break;
		case 8:
			torus[cell_num].can_acess_pos[0] = 4;
			torus[cell_num].can_acess_pos[1] = 11;
			torus[cell_num].can_acess_pos[2] = 9;
			torus[cell_num].can_acess_pos[3] = 12;
			torus[cell_num].can_acess_pid[0] = torus[4].pid;
			torus[cell_num].can_acess_pid[1] = torus[11].pid;
			torus[cell_num].can_acess_pid[2] = torus[9].pid;
			torus[cell_num].can_acess_pid[3] = torus[12].pid;
			break;
		case 9:
			torus[cell_num].can_acess_pos[0] = 5;
			torus[cell_num].can_acess_pos[1] = 8;
			torus[cell_num].can_acess_pos[2] = 10;
			torus[cell_num].can_acess_pos[3] = 13;
			torus[cell_num].can_acess_pid[0] = torus[5].pid;
			torus[cell_num].can_acess_pid[1] = torus[8].pid;
			torus[cell_num].can_acess_pid[2] = torus[10].pid;
			torus[cell_num].can_acess_pid[3] = torus[13].pid;
			break;
		case 10:
			torus[cell_num].can_acess_pos[0] = 6;
			torus[cell_num].can_acess_pos[1] = 9;
			torus[cell_num].can_acess_pos[2] = 11;
			torus[cell_num].can_acess_pos[3] = 14;
			torus[cell_num].can_acess_pid[0] = torus[6].pid;
			torus[cell_num].can_acess_pid[1] = torus[9].pid;
			torus[cell_num].can_acess_pid[2] = torus[11].pid;
			torus[cell_num].can_acess_pid[3] = torus[14].pid;
			break;
		case 11:
			torus[cell_num].can_acess_pos[0] = 7;
			torus[cell_num].can_acess_pos[1] = 10;
			torus[cell_num].can_acess_pos[2] = 8;
			torus[cell_num].can_acess_pos[3] = 15;
			torus[cell_num].can_acess_pid[0] = torus[7].pid;
			torus[cell_num].can_acess_pid[1] = torus[10].pid;
			torus[cell_num].can_acess_pid[2] = torus[8].pid;
			torus[cell_num].can_acess_pid[3] = torus[15].pid;
			break;
		case 12:
			torus[cell_num].can_acess_pos[0] = 8;
			torus[cell_num].can_acess_pos[1] = 15;
			torus[cell_num].can_acess_pos[2] = 13;
			torus[cell_num].can_acess_pos[3] = 0;
			torus[cell_num].can_acess_pid[0] = torus[8].pid;
			torus[cell_num].can_acess_pid[1] = torus[15].pid;
			torus[cell_num].can_acess_pid[2] = torus[13].pid;
			torus[cell_num].can_acess_pid[3] = torus[0].pid;
			break;
		case 13:
			torus[cell_num].can_acess_pos[0] = 9;
			torus[cell_num].can_acess_pos[1] = 12;
			torus[cell_num].can_acess_pos[2] = 14;
			torus[cell_num].can_acess_pos[3] = 1;
			torus[cell_num].can_acess_pid[0] = torus[9].pid;
			torus[cell_num].can_acess_pid[1] = torus[12].pid;
			torus[cell_num].can_acess_pid[2] = torus[14].pid;
			torus[cell_num].can_acess_pid[3] = torus[1].pid;
			break;
		case 14:
			torus[cell_num].can_acess_pos[0] = 10;
			torus[cell_num].can_acess_pos[1] = 13;
			torus[cell_num].can_acess_pos[2] = 15;
			torus[cell_num].can_acess_pos[3] = 2;
			torus[cell_num].can_acess_pid[0] = torus[10].pid;
			torus[cell_num].can_acess_pid[1] = torus[13].pid;
			torus[cell_num].can_acess_pid[2] = torus[15].pid;
			torus[cell_num].can_acess_pid[3] = torus[1].pid;
			break;
		case 15:
			torus[cell_num].can_acess_pos[0] = 11;
			torus[cell_num].can_acess_pos[1] = 14;
			torus[cell_num].can_acess_pos[2] = 12;
			torus[cell_num].can_acess_pos[3] = 3;
			torus[cell_num].can_acess_pid[0] = torus[11].pid;
			torus[cell_num].can_acess_pid[1] = torus[14].pid;
			torus[cell_num].can_acess_pid[2] = torus[12].pid;
			torus[cell_num].can_acess_pid[3] = torus[3].pid;
			break;	
		
	}
	
	
}


int main()
{

	cell_t torus[16];
	int i;
	
	/*for(i = 0; i < 16; i++){
		
		torus[i].pid = i;	
		
	}

	for(i = 0; i < 16 ; i++){
		
		ready_torus_cell(torus, i);
		printf("%d %d %d %d\n%d %d %d %d\n\n", torus[i].can_acess_pos[0], torus[i].can_acess_pos[1], torus[i].can_acess_pos[2], torus[i].can_acess_pos[3],
											   torus[i].can_acess_pid[0], torus[i].can_acess_pos[1], torus[i].can_acess_pos[2], torus[i].can_acess_pos[3]);	
		
	} Just a test to see ir it is working properly.*/
	
	
	
	return 0;
}

