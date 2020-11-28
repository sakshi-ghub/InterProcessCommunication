#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int Cat[5];
	int i;
	double temp[5];
	
	printf("Reading values of temperature......\n");
	int fd=open("average", O_RDONLY);
	read(fd, temp,sizeof(double)*5);
	//close(fd);

	/*printf("------\n");
	for(i=0;i<5;i++)
	{
		printf("%lf ",temp[i]);
	}	*/
	double avg, sd;
	//fd=open("average", O_RDONLY);
	
	printf("reading value of average and std deviation........\n");
	read(fd,&avg,sizeof(double));
	read(fd,&sd,sizeof(double));
	close(fd);

	/*printf("------%lf----\n",avg);
	printf("------%lf-----\n",sd);*/
	
	for(i=0;i<5;i++)
	{
		if(temp[i]==avg)
		{
			Cat[i]=0;
		}
		else if(temp[i]>avg+sd)
		{
			Cat[i]=1;
		}
		else if(temp[i]>avg && temp[i]<=avg+sd)
		{
			Cat[i]=2;
		}
		else if(temp[i]<avg && temp[i]>=avg-sd)
		{
			Cat[i]=3;
		}
		else if(temp[i]<avg)
		{
			Cat[i]=4;
		}
	}
	printf("Categories has been assigned temperature of each locations......\n");

	for(i=0;i<5;i++)
	{
		printf("L[%d] is in category %d\n",i,Cat[i]);
	}

	fd=open("Cat", O_WRONLY);
	write(fd,Cat,sizeof(int)*5);
	close(fd);
}

