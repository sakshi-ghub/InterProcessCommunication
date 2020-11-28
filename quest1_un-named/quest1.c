#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<math.h>

#define MSGSIZE sizeof(int)

int main(void)
{
	double L1,L2,L3,L4,L5;
	int i;

	int fd1[2];
	int fd2[2];
	int fd3[3];

	pid_t pid_A,pid_B;
	
	if(pipe(fd1)<0)
	{
		printf("pipe1 failed");
		return 1;
	}
	if(pipe(fd2)==-1)
	{
		printf("pipe2 failed");
		return 2;
	}
	if(pipe(fd3)==-1)
	{
		printf("pipe3 failed");
		return 3;
	}
	pid_A=fork();
	if(pid_A<0)
	{
		printf("fork1 failed");
		return 5;
	}
	else if(pid_A>0)
	{
		printf("Enter temperatures in range 15-45 of 5 locations\n");
		scanf("%lf%lf%lf%lf%lf",&L1,&L2,&L3,&L4,&L5);
		
		close(fd1[0]);
		
		write(fd1[1],&L1,sizeof(double));
		write(fd1[1],&L2,sizeof(double));
		write(fd1[1],&L3,sizeof(double));
		write(fd1[1],&L4,sizeof(double));
		write(fd1[1],&L5,sizeof(double));
		
		close(fd1[1]);
		
		wait(NULL);

		close(fd3[1]);

		int Cat[5];
		read(fd3[0],Cat,sizeof(int)*5);
	/*
		printf("=---------=\n");
		printf("%d%d%d%d%d",Cat[0],Cat[1],Cat[2],Cat[3],Cat[4]);
		printf("\n-------------\n");
	*/
		double  modified[5];
		modified[0]=L1;
		modified[1]=L2;
		modified[2]=L3;
		modified[3]=L4;
		modified[4]=L5;

		for(i=0;i<5;i++)
		{
			if(Cat[i]==1)
			{
				modified[i]-=3;
			}
			if(Cat[i]==2)
			{
				modified[i]-=1.5;
			}
			if(Cat[i]==3)
			{
				modified[i]+=2;
			}
			if(Cat[i]==4)
			{
				modified[i]+=2.5;
			}
		}

		printf("Revised temperature:\n");
		for(i=0;i<5;i++)
		{
			printf("L[%d]=%lf\n",i+1,modified[i]);
		}



	}
	else
	{
		close(fd1[1]);

                read(fd1[0],&L1,sizeof(double));
                read(fd1[0],&L2,sizeof(double));
                read(fd1[0],&L3,sizeof(double));
                read(fd1[0],&L4,sizeof(double));
                read(fd1[0],&L5,sizeof(double));

                close(fd1[0]);

		pid_B=fork();
		if(pid_B<0){
			printf("fork2 failed");
			return 6;
		}
		else if(pid_B>0)
		{
			double temp[5];
			wait(NULL);
			
			temp[0]=L1;
			temp[1]=L2;
			temp[2]=L3;
			temp[3]=L4;
			temp[4]=L5;

		/*	printf("---------------\n");
			printf("%lf %lf %lf %lf %lf",temp[0],temp[1],temp[2],temp[3],temp[4]);
			printf("--------------\n");
		*/
			close(fd2[1]);
			double avg, sd;
			read(fd2[0],&avg,sizeof(double));
			read(fd2[0],&sd,sizeof(double));
			close(fd2[0]);
		/*	
			printf("----avg=%lf----------\n",avg);
			printf("-----sd=%lf---------\n",sd);

		*/
			int Cat[5];
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
			close(fd3[0]);
			write(fd3[1],Cat,sizeof(int)*5);
			close(fd3[1]);

		}
		else{
			double sum,avg;

			//printf("%lf %lf %lf %lf %lf",L1,L2,L3,L4,L5);
			sum=L1+L2+L3+L4+L5;
			avg=sum/5;
			double sqdiff=(L1-avg)*(L1-avg)+(L2-avg)*(L2-avg)+(L3-avg)*(L3-avg)+(L4-avg)*(L4-avg)+(L5-avg)*(L5-avg);
			sqdiff/=5;
			sqdiff= sqrt(sqdiff);
			close(fd2[0]);

			write(fd2[1],&avg,sizeof(double));
			write(fd2[1],&sqdiff,sizeof(double));
			close(fd2[1]);


			//printf("finished");
		}


	}
}

