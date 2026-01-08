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
  int tail; /**< Index to write to */
  int head; /**< Index to read from */
  void **queue_data; /**< arr of void pointers */
  pthread_mutex_t mutex; /**< mutex which thread will compete for */
  pthread_cond_t not_full; /**< condition signaling if queue_data is not full */
  pthread_cond_t not_empty; /**< condition signaling if queue_data is not empty */
  int size; /** size of queue_data used to malloc space */ 
} QUEUE;


/**
 * @brief allocates memory strucuture to hold data in QUEUE
 * 
 * allocate space for the QUEUE struct and the arr it wraps 
 * inits the head and tail pointers 
 * inits the mutexes and conditions for thread sync
 *
 * @param[in] size_of_queue: the size of queue 
 * @return pointer to new QUEUE on success, null on failure
 * @warning make sure to check if fill pointer returned is valid
 *
*/
QUEUE *create_queue(int size_of_queue);


/**
 * @brief pushes a data into the queue
 * 
 * if queue isn't in use and isn't full data is enqueued 
 * otherwise this function will block until the prior is met 
 *
 * @param[in] queue: the queue to do work on 
 * @param[in] item_to_enq: the item to add to queue 
 * @return nothing
 * @warning currently enq has no timeout, can infinite block
 *
*/
void enq(QUEUE *queue, void *item_dequeued);

//TOOD
void deq(QUEUE *queue, void **item_dequeued); 
