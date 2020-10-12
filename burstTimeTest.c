#include "types.h"
#include "stat.h"
#include "user.h"

void delay()
{
	int a=0;
	while(a<1000000000)
	{
		int b=0;
		while(b<1000000000)
		{
			int c=0;
			while(c<1000000000)
			{
				int d=0;
				while(d<1000000000)
				{
					int e=1;
					int sum=0;
					while(e<=1000000000)
					{
						sum+=e;
						++e;
					}
					++d;
				}
				++c;
			}
			++b;
		}
		++a;
	}
}


int main(int argc, char* argv[])
{	
	if(setBurstTime(atoi(argv[1]))<0)
	{ 
		printf(0,"Error in setting burst time!");
		exit();
	}
	
	int pid1 = forkWithBurst(12);
	if(pid1 < 0) printf(1,"Error forking!\n");
	else if(pid1==0) printf(1,"In child 1\n");
	else
	{
		int pid2 = forkWithBurst(13);
		if(pid2<0) printf(1,"Error forking!\n");
		else if(pid2==0) printf(1,"In child 2\n");
		// else
		// {
		// 	wait();
		// 	wait();
		// }	
	}

	delay();

	printf(1,"%d\n",getBurstTime());
	exit();
}