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
  q->first = NULL;
  q->last = NULL;
}

bool_t queue_isempty(queue_t *q) {
  return (q->first == NULL && q->last == NULL);
}

void queue_enqueue(queue_t *q, pcb_t *pcb) {
  pcb_t *traverse;
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
      q->first = pcb;
      pcb->next = NULL;
    } else if (pcb->t < q->first->t) {
      pcb->next = q->first;
      q->first = pcb;
    }
    else {
      traverse = q->first; 
      while (traverse->next != NULL && traverse->next->t <= pcb->t)
      	traverse = traverse->next;
      pcb->next = traverse->next; 
      traverse->next = pcb;
    }
    break;
  }
}

pcb_t *queue_dequeue(queue_t *q) {
  pcb_t *temp;
  temp = q->first;
  ASSERT(!queue_isempty(q));
  q->first = q->first->next;
  if (q->first == NULL)
    q->last = NULL;
  return temp;
}

pcb_t *queue_peek(queue_t *q) {
  return q->first;
}
