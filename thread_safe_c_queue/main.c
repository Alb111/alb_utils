#include "queue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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
    printf("got %d\n", deq_item_int);
    if (deq_item_int != test->arr[i]) {
      printf("failed\n");
      return NULL;
    }
  }
  return NULL;
}

void *producer_thread(void *arg) {
  TEST_CASE *test = (TEST_CASE *)arg;
  for (int i = 0; i < test->size; i++) {
    printf("sent %d\n", test->arr[i]);
    enq(test->work_queue, &test->arr[i]);
  }
  return NULL;
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

  // bool producer_success = *(bool *)out1;
  // bool consumer_success = *(bool *)out2;

  return true;
}

bool fuzz_test(int num_to_test) {
  TEST_CASE rand_case;
  int *rand_nums;
  rand_nums = calloc(1000, sizeof(int));
  for (int i = 0; i < num_to_test; i++) {
    rand_nums[i] = rand();
  }
  rand_case.arr = rand_nums;
  rand_case.size = num_to_test;
  rand_case.work_queue = create_queue(num_to_test / 10);

  pthread_t producer, consumer;
  pthread_create(&consumer, NULL, consumer_thread, &rand_case);
  pthread_create(&producer, NULL, producer_thread, &rand_case);

  void *out1, *out2;

  pthread_join(producer, &out1);
  pthread_join(consumer, &out2);

  return true;
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
  if (!fuzz_test(10)) {
    printf("fuzz test failed\n");
    return 1;
  }
  return 0;
}
