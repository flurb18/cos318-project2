/* th3.c
 * COS 318, Fall 2019: Project 2 Non-Preemptive Kernel
 * Measures the time taken to context switch between threads
 */ 

#include "common.h"
#include "scheduler.h"
#include "util.h"

// Start and finish times of do_yield, for thread4 and thread5
uint64_t start;
uint64_t finish;

// IMPORTANT: thread4 must immediately precede thread5 in task[] (tasks.c)
void thread4(void) {
  start = get_timer();
  do_yield();
  do_exit();
}

void thread5(void) {
  finish = get_timer();
  print_str(0,0,"do_yield: ");
  print_int(0,10,(finish - start));
  do_exit();
}

// Timer threads to show how fair scheduling is

void thread6(void) {
  // start time
  uint64_t s;
  // total time
  uint64_t t = 0;
  while(1) {
    s = get_timer();
    print_str(20, 50, "Thread 6 CPU time: ");
    print_int(20, 69, t);
    t += get_timer() - s;
    do_yield();
  }
}

void thread7(void) {
  // start time
  uint64_t s;
  int i;
  // total time
  uint64_t t = 0;
  // dummy variable
  uint64_t dummy = 0;
  while(1) {
    s = get_timer();
    for(i = 0; i < 17; i++) {
      dummy++;
      print_int(21,69,dummy);
    }
    print_str(21,50, "Thread 7 CPU time: ");
    print_int(21,69, t);
    t += get_timer() - s;
    do_yield();
  }
}
