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
	shmPTR=(struct Memory*) shmat(shmid,NULL,0);
	/*if((int)shmPTR==-1)
	{
		printf("Error in attaching segment to data space");
		return 1;
	}*/
	shmPTR->status1 = NOT_READY;
	shmPTR->status2 = NOT_READY;
	shmPTR->status3 = NOT_READY;

	char password[10];
	while(1)
	{
		printf("Enter a 10 digit password:\n");
		scanf("%s", password);
		if(strlen(password) == 10)
			break;
		printf("password length is not 10, enter again\n");
	}

	for(int i=0;i<10;i++)
	{
		shmPTR->password[i]=password[i];
	}

	shmPTR->status1 =FILLED;

	while(shmPTR->status1 != TAKEN)
		sleep(1);

	while(shmPTR->status3 !=FILLED);

	if(shmPTR->strength ==0)
		printf("Weak password\n");
	else
		printf("Strong password\n");


	shmPTR->status3 = TAKEN;

	shmdt((void *)shmPTR);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
	
