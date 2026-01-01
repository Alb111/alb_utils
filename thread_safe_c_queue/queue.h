/**
 * @file queue.h
 * @brief Thread-safe circular queue implementation
 * @author Albert Felix
 * @date 2026-01-01
 * @version 1.0
*/

#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>


/**
 * @brief Thread-safe circular queue structure
 *
 * A thread safe queue structure that stores void pointers
 * It uses a circular buffer and stuff provided by POSIX
 * 
 * @warning The queue does not manage the memory of stored items
*/
typedef struct {
  int tail;
  int head;
  void *queue_data;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} QUEUE;

/**
 * @brief allocates memory strucuture to hold data in QUEUE
 * 
 * allocate space for the QUEUE struct and the arr it wraps 
 * inits the head and tail pointers 
 * inits the mutexes and conditions for thread sync
 *
 * @param[in] size_of_queue: the size of queue 
 * @param[in] size_of_queue_item: the size of queue 
 * @return pointer to new QUEUE on success, null on failure
 * @warning make sure to check if fill pointer returned is valid
 *
*/
QUEUE *create_queue(int size_of_queue, size_t size_of_queue_item);

// bool enq(QUEUE *queue, void *item_to_enq);
// bool deq(QUEUE *queue, void *deq_item);
