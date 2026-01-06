#include "queue.h"
#include <pthread.h>
#include <stdio.h>

// TEST: try to create a queue
bool test_init() {
  QUEUE *x = create_queue(10);
  if (!x) {
    return false;
  }
  return true;
}

// TEST: fuzz out edge cases
typedef struct {
  int *arr;
  int size;
  QUEUE *work_queue;
} TEST_CASE;

void *consumer_thread(void *arg) {
  TEST_CASE *test = (TEST_CASE *)arg;
  for (int i = 0; i < test->size; i++) {
    void *deq_item_void;
    deq(test->work_queue, &deq_item_void);

    int deq_item_int = *(int *)(deq_item_void);
    if (deq_item_int != test->arr[i]) {
      return (void *)false;
    }
  }
  return (void *)true;
}

void *producer_thread(void *arg) {
  TEST_CASE *test = (TEST_CASE *)arg;
  for (int i = 0; i < test->size; i++) {
    enq(test->work_queue, &test->arr[i]);
  }
  return (void *)true;
}

bool test_in_out() {

  // build out test case
  TEST_CASE in_out_test_case;
  int test_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  in_out_test_case.arr = test_arr;
  in_out_test_case.size = 10;
  in_out_test_case.work_queue = create_queue(10);

  pthread_t producer, consumer;
  pthread_create(&consumer, NULL, consumer_thread, &in_out_test_case);
  pthread_create(&producer, NULL, producer_thread, &in_out_test_case);

  void *out1, *out2;

  pthread_join(producer, &out1);
  pthread_join(consumer, &out2);

  bool producer_success = *(bool *)out1;
  bool consumer_success = *(bool *)out2;

  return producer_success & consumer_success;
}

int main() {
  if (!test_init()) {
    printf("init test failed\n");
    return 1;
  }
  if (!test_in_out()) {
    printf("in out test failed\n");
    return 1;
  }
  return 0;
}
