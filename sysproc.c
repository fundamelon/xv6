#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;
  argptr(0, (void*)&status, sizeof(status));
  exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int status_ptr;
  argptr(0, (void*)&status_ptr, sizeof(status_ptr));
  return wait((int*)status_ptr);
}

int sys_waitpid(void) {
    int pid;
    int status_ptr;
    int options;
    argptr(0, (void*)&pid, sizeof(pid));
    argptr(1, (void*)&status_ptr, sizeof(status_ptr));
    argptr(2, (void*)&options, sizeof(options));

    return waitpid(pid, (int*)status_ptr, options);
}

int
sys_change_priority(void) {
    int priority;
    argptr(0, (void*)&priority, sizeof(priority));

    return change_priority(priority);
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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
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
