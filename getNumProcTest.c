#include "types.h"
#include "stat.h"
#include "user.h"


int main(void)
{
	int ret = getNumProc();
	printf(1,"%d\n",ret);
	exit();
}