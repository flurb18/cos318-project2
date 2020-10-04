/* scheduler.c 
 * COS 318, Fall 2019: Project 2 Non-Preemptive Kernel
 * A non-preemptive scheduler
 */

#include "common.h"
#include "kernel.h"
#include "queue.h"
#include "scheduler.h"
#include "util.h"

int scheduler_count;

queue_t ready;
queue_t blocked;

void initialize_queues(pcb_t *pcbs, int num) {
  int i;
  queue_init(&ready);
  queue_init(&blocked);
  for (i = 0; i < num; i++)
    queue_enqueue(&ready, &pcbs[i]);
}

void scheduler(void) {
  ++scheduler_count;
  current_running = queue_dequeue(&ready);
  current_running->state = RUNNING;
}

void do_yield(void) {
  queue_enqueue(&ready, current_running);
  current_running->state = READY;
  scheduler_entry();
}

void do_exit(void) {
  current_running->state = EXITED;
  scheduler_entry();
}

void block(void) {
  queue_enqueue(&blocked, current_running);
  current_running->state = BLOCKED;
  scheduler_entry();
}

void unblock(void) {
  pcb_t *temp;
  if (blocked_tasks()) {
    temp = queue_dequeue(&blocked);
    queue_enqueue(&ready, temp);
  } 
}

bool_t blocked_tasks(void) {
  return (!queue_isempty(&blocked));
}
