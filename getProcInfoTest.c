#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[])
{
	
	int procid = atoi(argv[1]);
	struct processInfo pinf;
	pinf.ppid=0;
	pinf.psize=0;
	pinf.numberContextSwitches=0;

	//printf(0, "this is happening\n");
	//printf(1, "pointer %p\n", &pinf);
	// int x=1;
	// printf(1,"%d\n",x);

	// int x=69; int y=420; int z=710;
	// printf(3,"here2 %d\t%d\t%d\n", x, y, z);

	//printf(3,"here1 %d\t%d\t%d\n",pinf.ppid,pinf.psize,pinf.numberContextSwitches);	
	if(getProcInfo(procid,&pinf)<0)
	{ 
		printf(0,"Error process not found\n");
		exit();
	}

	int x=pinf.ppid; int y=pinf.psize; int z=pinf.numberContextSwitches;
	//
	printf(1, "%d ", x);
	printf(1, "%d ", y);
	printf(1,"%d\n", z);
	//printf(0,"reached here5\n");
	exit();
}