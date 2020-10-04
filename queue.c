/* queue.c
 * COS 318, Fall 2020: Project 2 Non-Preemptive Kernel
 * Queue data structure
 */

#include "common.h"
#include "kernel.h"
#include "queue.h"
#include "util.h"

void queue_init(queue_t *q, queuetype_t t) {
  q->type = t;
  switch(q->type) {
  case FIFO:
    q->first = NULL;
    q->last = NULL;
    break;
  case MIN_PRIORITY:
    q->root = NULL;
    break;
  default:
    ASSERT(0);
  }
}

bool_t queue_isempty(queue_t *q) {
  switch(q->type) {
  case FIFO:
    return (q->first == NULL && q->last == NULL);
  case MIN_PRIORITY:
    return (q->root == NULL);
  default:
    ASSERT(0);
  }
}

void queue_enqueue(queue_t *q, pcb_t *pcb) {
  pcb_t *current;
  int depth;
  switch(q->type) {
  case FIFO:
    if (queue_isempty(q)) {
      q->first = pcb;
      q->last = pcb;
      pcb->next = NULL;
    } else {
      q->last->next = pcb;
      q->last = pcb;
      pcb->next = NULL;
    }
    break;
  case MIN_PRIORITY:
    if (queue_isempty(q)) {
      q->root = pcb;
      pcb->parent = NULL;
      pcb->l = NULL;
      pcb->r = NULL;
    } else {
      current = q->root;
      while(1) {
	if(current->l == NULL) {
	}
      }
    }
    break;
  }
}

pcb_t *queue_dequeue(queue_t *q) {
  pcb_t *temp;
  switch(q->type) {
  case FIFO:
    temp = q->first;
    ASSERT(!queue_isempty(q));
    q->first = q->first->next;
    if (q->first == NULL)
      q->last = NULL;
    return temp;
  case MIN_PRIORITY:
    return NULL;
  default:
    ASSERT(0);
  }
}

pcb_t *queue_peek(queue_t *q) {
  switch(q->type) {
  case FIFO:
    return q->first;
  case MIN_PRIORITY:
    return q->root;
  default:
    ASSERT(0);
  }
}

pcb_t *queue_siftup(queue_t *q, pcb_t *pcb) {
  ASSERT(q->type == MIN_PRIORITY);
  ASSERT(!queue_isempty(q));
  pcb_t *current = pcb;
  do {
    if(current->parent == NULL)
      return current;
    
  } while(current->t < current->parent->t);
}
