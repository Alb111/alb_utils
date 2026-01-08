#include "queue.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

QUEUE *create_queue(int size_of_queue) {
  // head tail pointer require size to be greater than 1
  if (size_of_queue <= 1){
    fprintf(stderr, "Error: queue size must be greater than one\n");
    return NULL;
  }

  
  // try to allocate space
  QUEUE *q = calloc(1, sizeof(QUEUE));
  if (!q) {
    perror("Queue calloc failed in createQueue");
    return NULL;
  }

  q->queue_data = calloc(size_of_queue, sizeof(void *));
  if (!q->queue_data) {
    perror("Queue_data calloc failed in createQueue");
    return NULL;
  }

  // init mutex and thread conds
  if (pthread_mutex_init(&(q->mutex), NULL) != 0) {
    perror("Mutex init failed");
    return NULL;
  }
  if (pthread_cond_init(&(q->not_empty), NULL) != 0) {
    perror("cond init failed");
    return NULL;
  }
  if (pthread_cond_init(&(q->not_full), NULL) != 0) {
    perror("cond init failed");
    return NULL;
  }

  // set up pointers and size
  q->head = 0;
  q->tail = 0;
  q->size = size_of_queue;

  return q;
}

void enq(QUEUE *queue, void *item_to_enq) {

  // see if buffer is full, if it is wait for singal from deq
  pthread_mutex_lock(&(queue->mutex));
  int tail_plus_one = ((queue->tail + 1) % queue->size);
  while (tail_plus_one == queue->head) {
    // printf("waiting for deq\n");
    pthread_cond_wait(&(queue->not_full), &(queue->mutex));
  }
  queue->queue_data[queue->tail] = item_to_enq;
  queue->tail = tail_plus_one;
  pthread_mutex_unlock(&(queue->mutex));
  pthread_cond_signal(&(queue->not_empty));

  return;
}


void deq(QUEUE *queue, void **item_dequeued) {
  // see if buffer is empty, if it is wait for singal from deq
  pthread_mutex_lock(&(queue->mutex));
  int head_plus_one = ((queue->head + 1) % queue->size);
  while (queue->tail == queue->head) {
    // printf("waiting for enq\n");
    pthread_cond_wait(&(queue->not_empty), &(queue->mutex));
  }
  *item_dequeued = queue->queue_data[queue->head];
  queue->head = head_plus_one; 
  pthread_mutex_unlock(&(queue->mutex));
  pthread_cond_signal(&(queue->not_full));

  return;
}
