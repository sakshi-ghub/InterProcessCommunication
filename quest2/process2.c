#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>

#include<unistd.h>

#include "sharedMem.h"

int main()
{
	key_t key =ftok("shmfile",65);

	int shmid =shmget(key,1024,0666|IPC_CREAT);
	
	struct Memory *shmPTR;
	if (shmid < 0)
	{
		printf("Error in creating shared memory\n");
		return 1;
	}
	printf("Shared memory created in process2.......\n");
	shmPTR=(struct Memory*) shmat(shmid,NULL,0);
	/*if((int)shmPTR==-1)
	{
		printf("Error in attaching segment to data space");
		return 1;
	}*/

	while(shmPTR->status1 != FILLED);

	int alphanum=0, special=0,i;
	char c;

	for(i=0;i<10;i++)
	{
		c=shmPTR->password[i];
		if (isalpha(c) !=0 || isdigit(c) !=0)
			alphanum++;
		else
			special++;
	}

	shmPTR->status1=TAKEN;

	printf("alphanumeric character = %d, special character = %d\n",alphanum,special);
	shmPTR->alphanum=alphanum;
	shmPTR->special=special;

	printf("Process2 filled value.........\n");
	shmPTR->status2=FILLED;
	
	printf("Process3 needs to be started in other window....\n");
	while(shmPTR->status2 !=TAKEN)
		sleep(1);

	shmdt((void*)shmPTR);
	printf("Process2 exiting........\n");
	return 0;


}
