/* th3.c
 * COS 318, Fall 2019: Project 2 Non-Preemptive Kernel
 * Measures the time taken to context switch between threads
 */ 

#include "common.h"
#include "scheduler.h"
#include "util.h"

uint64_t start;
uint64_t finish;

// IMPORTANT: thread4 must immediately precede thread5

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
