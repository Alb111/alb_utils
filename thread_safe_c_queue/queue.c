#include "queue.h"
#include <string.h>
#include <stdio.h>

QUEUE *create_queue(int size_of_queue, size_t size_of_queue_item){
  // try to allocate space
  QUEUE *q = calloc(1, sizeof(QUEUE));
  if(!q){
    perror("Queue calloc failed in createQueue");
    return NULL;
  }

  q->queue_data = calloc(size_of_queue, size_of_queue_item);
  if(!q->queue_data){
    perror("Queue_data calloc failed in createQueue");
    return NULL;
  }

  // init mutex and thread conds
  if (pthread_mutex_init(&(q->mutex), NULL) != 0) {
    perror("Mutex init failed");
    return NULL;
  }
  if (pthread_cond_init(&(q->cond), NULL) != 0) {
    perror("cond init failed");
    return NULL;
  }
 
  // set up pointers
  q->head = 0;
  q->tail = 0;

  return q;
}



// bool enq(QUEUE *queue, QUEUE_ITEM *to_add) {
//   return true;
// }
// bool deq(QUEUE queue, QUEUE_ITEM to_add);
