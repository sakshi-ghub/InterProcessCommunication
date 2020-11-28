#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

int main()
{
	printf("enter temperature of 5 locations in range 15-45:\n");
	double L[5];
	int i;
	for(i=0;i<5;i++)
	{
		scanf("%lf",&L[i]);
	}
//	printf("taken input");
	int fd=open("temperature", O_WRONLY);
	write(fd,L,sizeof(double)*5);
	close(fd);
	
	int Cat[5];
	fd=open("Cat",O_RDONLY);
	read(fd,Cat,sizeof(int)*5);
	/*printf("---------");
	for(i=0;i<5;i++)
	{
		printf("%d ",Cat[i]);
	}
	printf("---------");*/
	close(fd);

		for(i=0;i<5;i++)
		{
			if(Cat[i]==1)
			{
				L[i]-=3;
			}
			if(Cat[i]==2)
			{
				L[i]-=1.5;
			}
			if(Cat[i]==3)
			{
				L[i]+=2;
			}
			if(Cat[i]==4)
			{
				L[i]+=2.5;
			}
		}

		printf("Revised temperature:\n");
		for(i=0;i<5;i++)
		{
			printf("L[%d]=%lf\n",i+1,L[i]);
		}
	//close(fd1);
	
}
