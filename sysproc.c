#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processInfo.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the number of non-UNUSED state processes in
// the process table.
int
sys_getNumProc(void)
{
  int num=0;
  activeProcs();
  cprintf("\n");
  num = numProc();

  return num;
}

// returns the number of processes that are occupying a 
// slot in the process table.
int
sys_getMaxPid(void)
{
  activeProcs();
  cprintf("\n");
  int pid=0;
  pid=maxPid();

  return pid;
}

int 
sys_getProcInfo(void)
{
  activeProcs();
  cprintf("\n");
  int procid;
  argint(0,&procid);

  
  int dum;
  argint(1,&dum);
  struct processInfo *pinf = (struct processInfo*)dum;

  
  struct proc *currproc=0;
  if((currproc=procInfo(procid))==0) return -1;

  
  pinf->ppid = ((currproc->parent)->pid<=0 ? 0:(currproc->parent)->pid);
  pinf->psize = (int)currproc->sz;
  pinf->numberContextSwitches = currproc->numSwitched;

  return 0;
}


int
sys_setBurstTime(void)
{
  //activeProcs();
  //cprintf("\n");
  struct proc *currproc = myproc();

  int burst=0;
  if(argint(0,&burst)<0) return -1;

  if(burst<0 || burst>20) return -1;

  currproc->burstTime=burst;
  return 0;
}


int
sys_getBurstTime(void)
{
  return myproc()->burstTime;
}

int
sys_forkWithBurst(void)
{
  int pid = fork();
  struct proc *currproc;
  currproc = procInfo(pid);

  int burst;
  argint(0,&burst);

  currproc->burstTime = burst;

  return currproc->pid;
}
