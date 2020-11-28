#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<math.h>

int main()
{
	double sum=0,avg,sqdiff=0;
	int fd=open("temperature", O_RDONLY);
	double L[5];
	printf("Reading values of temperature from pipe......\n");
	read(fd, L,sizeof(double)*5);
	close(fd);

	int i;
	printf("Temperature at different locations...\n");
	printf("--------\n");
	for(i=0;i<5;i++)
	{
		printf("L[%d]=%lf ",i,L[i]);
	}
	printf("\n");
	printf("------\n");
	for(i=0;i<5;i++)
	{
		sum+=L[i];
	}

	avg=sum/5;

	for(i=0;i<5;i++)
	{
		sqdiff+=(L[i]-avg)*(L[i]-avg);
	}

	sqdiff/=5;
	sqdiff= sqrt(sqdiff);
	
	fd=open("average", O_WRONLY);
	write(fd,L,sizeof(double)*5);
	write(fd,&avg,sizeof(double));
	write(fd,&sqdiff,sizeof(double));
	printf("----avg of temperatures=%lf-----\n",avg);
	printf("----std deviation of temperatures=%lf----\n",sqdiff);
	
	close(fd);
}
