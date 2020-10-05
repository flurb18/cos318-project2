/* queue.h
 * COS 318, Fall 2020: Project 2 Non-Preemptive Kernel
 * Definitions and types for queue data structure
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"
#include "kernel.h"

// Type of queue - first in first out or minimum priority (based on pcb->t)
typedef enum { FIFO, MIN_PRIORITY } queuetype_t;

// Queue data type - we only actually need a couple of pcb pointers since
// they're internally linked
typedef struct {
  queuetype_t type;
  pcb_t *first;
  pcb_t *last;
} queue_t;

// Initialize a queue to a certain type
void queue_init(queue_t *q, queuetype_t t);

// Return whether this queue is empty
bool_t queue_isempty(queue_t *q);

// Add a pcb to this queue, based on the type of queue it is
void queue_enqueue(queue_t *q, pcb_t *pcb);

// Remove a pcb from this queue, based on the type of queue it is
pcb_t *queue_dequeue(queue_t *q);

// Show the element that would be removed by a dequeue()
pcb_t *queue_peek(queue_t *q);

#endif
