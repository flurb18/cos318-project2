/* kernel.h
 * COS 318, Fall 2020: Project 2 Non-Preemptive Kernel
 * Definitions and types used by kernel code
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"

// ENTRY_POINT points to a location that holds a pointer to kernel_entry
#define ENTRY_POINT ((void (**)(int)) 0x0f00)

// System call numbers
enum {
    SYSCALL_YIELD,
    SYSCALL_EXIT,
};

// All stacks should be STACK_SIZE bytes large
// The first stack should be placed at location STACK_MIN
// Only memory below STACK_MAX should be used for stacks
enum {
    STACK_MIN = 0x40000,
    STACK_SIZE = 0x1000,
    STACK_MAX = 0x52000,
};

typedef struct pcb {
  // Stack
  uint32_t esp;
  // Next pcb in the FIFO queue this pcb is in
  struct pcb *next;
  // Parent and children in the min priorty queue
  struct pcb *parent;
  struct pcb *l;
  struct pcb *r;
  // Time elapsed since initialization
  uint64_t t;
  // Process ID
  uint16_t pid;
  // State of the process
  enum {
    RUNNING,
    READY,
    BLOCKED,
    EXITED
  } state;
} pcb_t;

// The task currently running
extern pcb_t *current_running;

void kernel_entry(int fn);

#endif
