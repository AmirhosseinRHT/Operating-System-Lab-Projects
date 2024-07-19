#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "prioritylock.h"

void
initprioritylock(struct prioritylock *lk, char *name)
{
  initlock(&lk->lk, "priority lock");
  lk->name = name;
  lk->locked = 0;
  lk->pid = 0;
  lk->priority_queue = 0;
}

void
acquirepriority(struct prioritylock *lk)
{
  acquire(&lk->lk);
  if (lk->locked) {
    add_to_priority_list(&(lk->priority_queue), myproc());
    cprintf("\nprocess: %d added", myproc()->pid);
    monitor_pqueue(lk);
    while(lk->locked){
      sleep(lk, &lk->lk);
    }
  }
  lk->locked = 1;
  lk->pid = myproc()->pid;
  release(&lk->lk);
}

void
releasepriority(struct prioritylock *lk)
{
  acquire(&lk->lk);
  
  if(lk->pid != myproc()->pid){
    release(&lk->lk);
    return;
  }
  struct proc* proc = get_highest_priority(&(lk->priority_queue));
  lk->locked = 0;
  lk->pid = 0;
  cprintf("\nprocess: %d released", myproc()->pid);
  if (proc != 0){
    cprintf("\nnext process: %d", proc->pid);
  }
  monitor_pqueue(lk);
  if (proc != 0){
    wakeup(lk);
  }
  release(&lk->lk);
}

int
holdingpriority(struct prioritylock *lk)
{
  int r;
  acquire(&lk->lk);
  r = lk->locked && (lk->pid == myproc()->pid);
  release(&lk->lk);
  return r;
}

void add_to_priority_list(struct pqueue **queue, struct proc* proc){
  struct pqueue* current = (struct pqueue*)kalloc();
  if (current == 0){
    panic("can't allocate memory for priority queue");
  }
  current->proc = proc;
  struct pqueue* head = *queue;
  if (head == 0){
    current->next = 0;
    *queue = current;
    cprintf("\n added");
    return;
  }
  if (head->proc->pid > current->proc->pid){
    current->next = head;
    head->next = 0;
    *queue = current;
    return;
  }
  while(1){
    if (head->next == 0){
      current->next = 0;
      head->next = current;
      break;
    }
    if (head->next->proc->pid < current->proc->pid){
      head = head->next;
    }
    else{
      struct pqueue* temp = head->next;
      head->next = current;
      current->next = temp;
      break;
    }
  }
}

struct proc* get_highest_priority(struct pqueue **queue){
  if (*queue == 0){
    return 0;
  }
  struct proc* ans = (*queue)->proc;
  struct pqueue* temp = (*queue)->next;
  kfree((char *)(*queue));
  *queue = temp;

  return ans;
}

void monitor_pqueue(struct prioritylock *lk){
  struct pqueue* head = lk->priority_queue;
  cprintf("\npid that uses lock : %d \n", lk->pid);
  cprintf("priority lock :\n");
  if (head == 0){
    return;
  }
  int i = 1;
  while(1){
    if (head == 0){
      break;
    }
    cprintf("%d- pid : %d\n", i, head->proc->pid);
    head = head->next;
  }
}