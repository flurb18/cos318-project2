/* queue.h
 * COS 318, Fall 2020: Project 2 Non-Preemptive Kernel
 * Definitions and types for queue data structure
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"
#include "kernel.h"

typedef struct {
  pcb_t *first;
  pcb_t *last;
} queue_t;

void queue_init(queue_t *q);

bool_t queue_isempty(queue_t *q);

void queue_enqueue(queue_t *q, pcb_t *pcb);

pcb_t *queue_dequeue(queue_t *q);

pcb_t *queue_peek(queue_t *q);

#endif
