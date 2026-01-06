#include "queue.h"
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

void *cosumer_thread(void *arg) {
  TEST_CASE*test = (TEST_CASE*)arg;
  for(int i = 0; i < test->size; i++)
  {
    void *deq_item_void;
    deq(test->work_queue, &deq_item_void);

    int deq_item_int = *(int *)(deq_item_void);
    if(deq_item_int != test->arr[i]){
      return false;
    }
  }
  return true;
}

int main() {
  if (!test_init()) {
    printf("init test failed\n");
    return 1;
  }

  return 0;
}
