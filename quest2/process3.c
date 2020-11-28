#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
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
	printf("Process3 created shared memory......\n");

	shmPTR=(struct Memory*) shmat(shmid,NULL,0);

	while(shmPTR->status2 != FILLED);

	int strength;

	if(shmPTR->alphanum>= shmPTR->special)
		strength=0;

	else
		strength=1;

	shmPTR->status2=TAKEN;


	shmPTR->strength = strength;

	shmPTR->status3=FILLED;
	
	printf("Calculated strength of password and written in shared file.....\n");

	while( shmPTR->status3 !=TAKEN)
		sleep(1);

	shmdt((void*)shmPTR);

	printf("Process3 exiting.........\n");
	return 0;
}
