#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;

  if(argint(0, &status) < 0) 
  {
    return -1; //returns -1 if the assignment fails
  }

  exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int *status;

  if (argptr(0, (char **)&status,sizeof(status))<0) {
    return -1;
  }
  
  return wait(status);
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

//Lab 0 Task
int
sys_add(void)
{
  int a = 1;
  int b = 2020;
  //initialize the variable c, and try to get some value to it
  int c;
  int d;

  /* 0 means to take in the first argument - if there was a 1, that means take in the second argument
     so, take the first value and assign it to the value c is what argint(0, &c) means. */
  if(argint(0, &c) < 0) 
  {
    return -1; //returns -1 if the assignment fails
  }

  if(argint(1, &d) < 0)
  {
    return -1;
  }

  return a+b+c+d;
}

//Lab 1 Part A
int
sys_getppid(void)
{
  return myproc()->parent->pid;
}

//Lab 1 Part D
int
sys_ps(void)
{
  return ps();
}

//Lab 2
int
sys_setpriority()
{
  int newPriority;

  if(argint(0, &newPriority) < 0) 
  {
    newPriority = 0; //returns lowest priority if the assignment fails
  }
  else if(argint(0, &newPriority) > 31) {
    newPriority = 31;
  }

  myproc()->priorityNumber = newPriority;

  yield();

  return 0;
}

//Lab 2
int
sys_getpriority(void)
{
  return myproc()->priorityNumber;
}
