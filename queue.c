/* queue.c
 * COS 318, Fall 2020: Project 2 Non-Preemptive Kernel
 * Queue data structure
 */

#include "common.h"
#include "kernel.h"
#include "queue.h"
#include "util.h"

void queue_init(queue_t *q) {
  q->first = NULL;
  q->last = NULL;
}

bool_t queue_isempty(queue_t *q) {
  return (q->first == NULL && q->last == NULL);
}

void queue_enqueue(queue_t *q, pcb_t *pcb) {
  if (queue_isempty(q)) {
    q->first = pcb;
    q->last = pcb;
    pcb->next = NULL;
  } else {
    q->last->next = pcb;
    pcb->next = NULL;
    q->last = pcb;
  }
}

pcb_t *queue_dequeue(queue_t *q) {
  pcb_t *temp = q->first;
  ASSERT(!queue_isempty(q));
  if (q->first == q->last) {
    queue_init(q);
    return temp;
  }
  q->first = q->first->next;
  return temp;
}

pcb_t *queue_peek(queue_t *q) {
  return q->first;
}
