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
  // Change FIFO to MIN_PRIORITY in this line for extra credit
  queue_init(&ready, FIFO);
  // This should always be FIFO
  queue_init(&blocked, FIFO);
  for (i = 0; i < num; i++) {
    queue_enqueue(&ready, &pcbs[i]);
  }
}

void scheduler(void) {
  ++scheduler_count;
  if (queue_isempty(&ready)) {
    while(1)
      print_str(0,0,"No more tasks to run!");
  }
  current_running = queue_dequeue(&ready);
  current_running->state = RUNNING;
  current_running->start = get_timer();
}

void do_yield(void) {
  current_running->t += get_timer() - current_running->start;
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
  ASSERT(blocked_tasks());
  queue_enqueue(&ready, queue_dequeue(&blocked));
}

bool_t blocked_tasks(void) {
  return (!queue_isempty(&blocked));
}
