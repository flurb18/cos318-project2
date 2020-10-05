/* scheduler.h
 * COS 318, Fall 2020: Project 2 Non-Preemptive Kernel
 * Definitions and types for a non-preemtive scheduler
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "common.h"
#include "kernel.h"

// Number of times scheduler() was called
extern int scheduler_count;

// Save the context and the kernel stack before calling scheduler
// This function is implemented in entry.S
void scheduler_entry(void);

// Initialize the ready queue and the blocked queue
void initialize_queues(pcb_t *pcbs, int num);

// Change current_running to the next task
void scheduler(void);

// Update current_running's start time (called at the end of scheduler_entry)
void update_time_started(void);

// Schedule another task
// Call from a kernel thread or kernel_entry_helper()
void do_yield(void);

// Schedule another task but do not reschedule the current one
// Call from a kernel thread or kernel_entry_helper()
void do_exit(void);

// Put the currently running task on the blocked queue
void block(void);

// If there is a task on the blocked queue, move it to the ready queue
void unblock(void);

// Returns TRUE if there are blocked tasks, FALSE otherwise
bool_t blocked_tasks(void);

#endif
